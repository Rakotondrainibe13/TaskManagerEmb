#pragma once

#include <QObject>
#include "../include/network_config.h"

class NetworkConfigController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serverIP READ serverIP WRITE setServerIP NOTIFY serverIPChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

public:
    explicit NetworkConfigController(QObject *parent = nullptr);

    QString serverIP() const;
    Q_INVOKABLE void setServerIP(const QString &serverIP);

    int port() const;
    Q_INVOKABLE void setPort(int port);

    Q_INVOKABLE void loadConfig();
    Q_INVOKABLE void saveConfig();

signals:
    void serverIPChanged();
    void portChanged();
    void configLoaded();
    void configSaved();

private:
    NetworkConfig m_networkConfig;
};
