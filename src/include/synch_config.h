#pragma once

#include <QString>
#include <QObject>

class SynchConfig : public QObject
{
    Q_OBJECT
public:
    SynchConfig(QObject* parent);
    ~SynchConfig();
    QString backUpDirectory;
    QString gpgBinaryPath;
    QString ipServerCentral;
    QString port;
    QString username;
    QString password;
    QString remoteServer;

    QString parseValue(const QString& line, const QString& key);
    void saveConfig(const QString &filename);
};
