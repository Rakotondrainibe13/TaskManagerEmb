#include "../include/synch_manager.h"
#include "../include/synch_config.h"
std::shared_ptr<SynchManager> SynchManager::s_instance = nullptr;
QMutex SynchManager::mutex;
std::shared_ptr<SynchManager> SynchManager::getInstance(QObject *parent){
    if (!s_instance) {
        mutex.lock();
        if (!s_instance) {
            s_instance = std::make_shared<SynchManager>(parent);
        }
        mutex.unlock();
    }
    return s_instance;
}
SynchManager::SynchManager(QObject *parent): 
    QObject(parent),
    m_encryptionService(std::make_unique<EncryptionService>()),
    m_config(std::make_unique<SynchConfig>(this))
{
    // fichier de configuration pour eviter de modifier dans le code
    m_config->saveConfig("./config.ini");

    // set sshManager
    m_sshManager = std::make_unique<SSHManager>(m_config->ipServerCentral, m_config->port, m_config->username, m_config->password,this);

    m_backupDirectory = m_config->backUpDirectory;
};
SynchManager::~SynchManager(){};
void SynchManager::startSync(){
    try {
    // create .dump file
        QString command = "sqlite3 database.db .dump > database.dump";
        m_sshManager->executeCommand(command);
    // encrypte the .dump file
        QString filePath = "./database.dump";
        EncryptionService encrypte;
        encrypte.setM_gpgBinaryPath(m_config->gpgBinaryPath);
        encrypte.generateKeyPair();
        QString encrypte_file_name = encrypte.encryptFile(filePath);
    // execute the command to move the file after cryptage
        QString commandMove = "mv " + encrypte_file_name + " " + m_backupDirectory;
        m_sshManager->executeCommand(commandMove);
    // send the back_up file to central server
        sendFile();
        emit synchCompleted("Synchronization and backup completed successfully!!");
    } catch (const ExceptionManager &e) {
        emit synchCompleted(e.message());
    }
}

void SynchManager::retentionBackup(int &mois, int &jour, int &heure, int &minute){
     if (mois == 0 && jour == 0 && heure == 0 && minute == 0) {
        emit retentionConfigCompleted("Failed","All parameters (month, day, hour, minute) are set to 0. Retention has not been configured.");
        throw ExceptionManager("All parameters (month, day, hour, minute) are set to 0. Retention has not been configured.");
    }
    
    QString directory = m_backupDirectory;

    if (directory == "" || directory.isEmpty())
    {
        throw ExceptionManager("ERROR directory file is empty.");
    }

    if (directory == "" || directory.isEmpty())
    {
        throw ExceptionManager("ERROR directory file is empty.");
    }

    QString minuteStr = (minute == 0) ? "*" : QString::number(minute);
    QString heureStr = (heure == 0) ? "*" : QString::number(heure);
    QString jourStr = (jour == 0) ? "*" : QString::number(jour);
    QString moisStr = (mois == 0) ? "*" : QString::number(mois);

    QString cronJob = QString("%1 %2 %3 %4 * rm -rf '%5'/*")
                        .arg(minuteStr)
                        .arg(heureStr)
                        .arg(jourStr)
                        .arg(moisStr)
                        .arg(directory);

    QString removeOldCronJob = QString("crontab -l 2>/dev/null | grep -v '%1' | crontab -").arg(directory);
    int result = system(removeOldCronJob.toStdString().c_str());

    if (result != 0) {
        emit retentionConfigCompleted("Failed","Error while removing the old configuration.");
        throw ExceptionManager("Error while configuring the retention.");
    }

    QString addCronJob = QString("(crontab -l 2>/dev/null; echo \"%1\") | crontab -").arg(cronJob);
    result = system(addCronJob.toStdString().c_str());

    if (result == 0) {
        emit retentionConfigCompleted("Success","Retention successfully configured.");
    } else {
        emit retentionConfigCompleted("Failed","Error while configuring the retention.");
        throw ExceptionManager("Error while configuring the retention.");
    }

};
void SynchManager::createDumpFile(){};
void SynchManager::sendFile(){
    try
    {
        QString sshCommand = m_sshManager->createCommandSSH(m_backupDirectory, m_config->remoteServer);
        m_sshManager->executeCommand(sshCommand);
    }
    catch (const ExceptionManager &e) {
        throw e.message();
    }
    
};
void SynchManager::receiveFile(){};

