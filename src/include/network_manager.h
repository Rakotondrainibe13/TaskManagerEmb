#pragma once
#include "network_command.h"
#include "network_monitor.h"
#include "network_config.h"
#include "udp_send_command.h"
#include "close_connection_command.h"
#include "open_connection_command.h"
#include "receive_data_command.h"
#include "send_data_command.h"
#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QVariantList>
#include <QVector>
#include <QTimer>
#include <QQueue>
#include <memory>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    // Méthode pour obtenir l'instance unique de NetworkManager
    static NetworkManager &instance();

    // Suppression des méthodes de copie et d'affectation
    NetworkManager(const NetworkManager &) = delete;
    NetworkManager &operator=(const NetworkManager &) = delete;
    ~NetworkManager();

    void sendData(const QByteArray &data);
    void executeCommand(NetworkCommand *command);

    std::shared_ptr<QTcpSocket> getTcpSocket();
    std::shared_ptr<QUdpSocket> getUdpSocket();

    NetworkConfig* getNetworkConfig() const;
    void setNetworkConfig(NetworkConfig config);

    Q_INVOKABLE QVariantList getLogs() const;

public slots:
    void
    saveConfig(const QString &serverIP, const QString &port);

private:
    QQueue<NetworkCommand *> commandQueue;
    std::shared_ptr<QTcpSocket> tcpSocket;
    std::shared_ptr<QUdpSocket> udpSocket;
    QVector<NetworkLog> * logs;
    QTimer *monitorTimer;
    NetworkMonitor *monitor;
    NetworkConfig* config;

    explicit NetworkManager(QObject *parent = nullptr);
    void processNextCommand();
};
