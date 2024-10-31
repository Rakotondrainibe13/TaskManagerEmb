#include "../include/network_config.h"
#include <QSettings>
#include <QDebug>
#include <iostream>
#include <QFile>

void NetworkConfig::loadConfig(const QString &filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    settings.beginGroup("Network");
    serverIP = settings.value("ServerIP", "0.0.0.0").toString();
    port = settings.value("Port", 0).toInt();
    settings.endGroup();
}

void NetworkConfig::saveConfig(const QString &filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    qDebug() << serverIP << filename << port;
    settings.setValue("Network/ServerIP", serverIP);
    settings.setValue("Network/Port", port);
}
