#ifndef SSH_MANAGER_H
#define SSH_MANAGER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QDebug>
#include "exception_manager.h"

class SSHManager : public QObject
{
    Q_OBJECT
public:
    SSHManager(const QString& host, QString port, const QString& username, const QString& password, QObject* parent);
    SSHManager();
    ~SSHManager();

    QString executeCommand(const QString& command);
    QString createCommandSSH(const QString &path, const QString& remoteServer);

    void setHost(const QString& host) {
        host_ = host;
    }
    void setPort(QString port) {
        port_ = port;
    }
    void setUsername(const QString& username) {
        username_ = username;
    }
    void setPassword(const QString& password) {
        password_ = password;
    }

signals:
    void operationCompleted(QString response);

private:
    QString host_;
    QString port_;
    QString username_;
    QString password_;
};

#endif
