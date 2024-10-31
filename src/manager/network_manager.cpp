#include "../include/network_manager.h"

// Initialisation de l'instance unique de NetworkManager
NetworkManager &NetworkManager::instance()
{
    static NetworkManager instance;
    return instance;
}

NetworkConfig* NetworkManager::getNetworkConfig() const {
    return config;
}

void NetworkManager::setNetworkConfig(NetworkConfig configuration) {
    config = &configuration;
    config->saveConfig("../../config.ini");
}

std::shared_ptr<QTcpSocket> NetworkManager::getTcpSocket()
{
    return tcpSocket;
}

std::shared_ptr<QUdpSocket> NetworkManager::getUdpSocket()
{
    return udpSocket;
}

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    tcpSocket = std::make_shared<QTcpSocket>(this);
    udpSocket = std::make_shared<QUdpSocket>(this);
    config = new NetworkConfig();
    config->loadConfig("../../config.ini");
    logs = new QVector<NetworkLog>();

    OpenConnectionCommand opencommand(tcpSocket, config->serverIP, config->port);
    executeCommand(&opencommand);
    QByteArray data("Hello, Mande!");
    SendDataCommand sendcommand(tcpSocket, data);
    executeCommand(&sendcommand);
    ReceiveDataCommand receivedatacommand(tcpSocket);
    executeCommand(&receivedatacommand);

    // monitorTimer = new QTimer(this);
    // monitor = new NetworkMonitor(this);

    // connect(monitorTimer, &QTimer::timeout, this, &NetworkManager::processNextCommand);
    // monitorTimer->start(100);

    // monitor->startMonitoring();
}

QVariantList NetworkManager::getLogs() const {
    QVariantList logList;
    for (const auto& log : *logs) {
        QVariantMap logMap;
        logMap["timestamp"] = log.getTimestamp().toString("yyyy-MM-dd HH:mm:ss");
        logMap["server"] = log.getServer();
        logMap["status"] = log.getStatus();
        logMap["response"] = log.getResponse();
        logList.append(logMap);
    }
    return logList;
}

void NetworkManager::saveConfig(const QString &serverIP, const QString &port)
{
    config->serverIP = serverIP;
    config->port = port.toInt();
    config->saveConfig("../../config.ini");
}

NetworkManager::~NetworkManager()
{
    while (!commandQueue.isEmpty())
    {
        delete commandQueue.dequeue();
    }
    if (config != nullptr)
    {
        delete config;
    }
    delete logs;
}

void NetworkManager::sendData(const QByteArray &data)
{
    auto command = new SendDataCommand(tcpSocket, data);
    commandQueue.enqueue(command);
}

void NetworkManager::executeCommand(NetworkCommand *command)
{
    commandQueue.enqueue(command);
    processNextCommand();
}

void NetworkManager::processNextCommand()
{
    if (!commandQueue.isEmpty())
    {
        NetworkCommand *command = commandQueue.dequeue();
        command->execute();
        QDateTime timestamp = QDateTime::currentDateTime();
        QString server = config->serverIP + ":" + QString::number(config->port);
        QString status = "success";
        QString response = "{}";
        if(command->typeName() == "ReceiveDataCommand"){
            ReceiveDataCommand *receiveCommand = dynamic_cast<ReceiveDataCommand *>(command);
            QString longResponse = receiveCommand->getReceivedData();
            QString shortResponse = longResponse.left(4) + (longResponse.length() > 4 ? "..." : "");
            response = shortResponse;
        }
        NetworkLog networklog(timestamp, server, status, response);
        logs->append(networklog);
    }
}
