#include "network_config_controller.h"

NetworkConfigController::NetworkConfigController(QObject *parent)
    : QObject(parent)
{
    m_networkConfig.loadConfig("../../config.ini");
}

QString NetworkConfigController::serverIP() const
{
    return m_networkConfig.serverIP;
}

void NetworkConfigController::setServerIP(const QString &serverIPs)
{
    if (m_networkConfig.serverIP != serverIPs) {
        m_networkConfig.serverIP = serverIPs;
        emit serverIPChanged();
    }
}

int NetworkConfigController::port() const
{
    return m_networkConfig.port;
}

void NetworkConfigController::setPort(int ports)
{
    if (m_networkConfig.port != ports) {
        m_networkConfig.port = ports;
        emit portChanged();
    }
}

void NetworkConfigController::loadConfig()
{
    m_networkConfig.loadConfig("../../config.ini");
    emit configLoaded();
    emit serverIPChanged();
    emit portChanged();
}

void NetworkConfigController::saveConfig()
{
    m_networkConfig.saveConfig("../../config.ini");
    emit configSaved();
    emit serverIPChanged();
    emit portChanged();
}
