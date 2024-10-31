#ifndef SYNCH_MANAGER_H
#define SYNCH_MANAGER_H

#include <QString>
#include <QMutex>
#include <QDebug>
#include "ssh_manager.h"
#include "encryption_service.h"
#include "synch_config.h"
#include "exception_manager.h"

class SynchManager : public QObject {
Q_OBJECT
public:
    explicit SynchManager(QObject *parent = nullptr);
    static std::shared_ptr<SynchManager> getInstance(QObject *parent = nullptr);
    virtual ~SynchManager();
    void startSync();
    void retentionBackup(int& mois, int& jour, int& heure, int& minute);
    void createDumpFile();
    void sendFile();
    void receiveFile();

signals:
    void synchCompleted(QString response);
    void retentionConfigCompleted(QString response, QString result);
private:
    SynchManager(const SynchManager&) = delete;
    SynchManager& operator=(const SynchManager&) = delete;
    static std::shared_ptr<SynchManager> s_instance;
    static QMutex mutex;
    QString m_backupDirectory;
    std::unique_ptr<SSHManager> m_sshManager;
    std::unique_ptr<EncryptionService> m_encryptionService;
    // std::unique_ptr<DatabaseManager> m_dbManager;
    std::unique_ptr<SynchConfig> m_config;
};
    


#endif

