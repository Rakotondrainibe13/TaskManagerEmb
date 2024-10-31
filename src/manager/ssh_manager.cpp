#include "../include/ssh_manager.h"
SSHManager::SSHManager(const QString& host, QString port, const QString& username, const QString& password,QObject* parent)
        : host_(host), port_(port), username_(username), password_(password), QObject(parent) {};
SSHManager::SSHManager(){};
SSHManager::~SSHManager(){};

QString SSHManager::createCommandSSH(const QString &path, const QString& remoteServer){
    // return "sshpass -p "+password_+" ssh -o StrictHostKeyChecking=no "+username_+"@"+host_;
    return "sshpass -p '"+password_+"' rsync -avz --compress-level=6 -e ssh \"$(find '"+path+"' -type f -name '*.gpg' -printf '%T@ %p\n' | sort -n | tail -1 | cut -d' ' -f2-)\" "+username_+"@"+host_+":"+remoteServer+"";
}

QString SSHManager::executeCommand(const QString &command) {
    QProcess process;
    QStringList arguments;
    arguments << "-c" << command;
    process.start("bash", arguments);

    if (!process.waitForStarted()) {
        throw ExceptionManager("Error starting process");
    }

    if (!process.waitForFinished()) {
        QString error = process.errorString();
        throw ExceptionManager("Error waiting for process to finish");
    }

    QString result = process.readAllStandardOutput().trimmed();
    QString error = process.readAllStandardError().trimmed();

    if (!error.isEmpty()) {
        throw ExceptionManager("SSH Error");
    }

    return result;
}
