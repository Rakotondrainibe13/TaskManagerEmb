#pragma once

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QFile>
#include <QTextStream>
#include "network_log.h"

class NetworkMonitor : public QObject {
    Q_OBJECT
public:
    explicit NetworkMonitor(QObject *parent = nullptr);

    void startMonitoring();
    void stopMonitoring();
    void addLog(const NetworkLog& log);
    QVector<NetworkLog> getLogs() const;

signals:
    void logAdded(const NetworkLog& log);

private slots:
    void onMonitoringTimeout();

private:
    QVector<NetworkLog> logs;
    QTimer monitorTimer;

    qint64 totalBytesSent;
    qint64 totalBytesReceived;
    qint64 previousBytesSent;
    qint64 previousBytesReceived;

    void checkNetworkInterfaces();
    void checkTcpConnections();
    void checkUdpConnections();
    void updateNetworkStats();
    void detectNetworkErrors();
};
