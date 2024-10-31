#pragma once

#include <QDateTime>
#include <QString>

class NetworkConfig
{
public:
    QString serverIP;
    int port;

    void loadConfig(const QString &filename);
    void saveConfig(const QString &filename);
};