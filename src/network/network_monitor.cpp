#include "../include/network_monitor.h"
#include <QDebug>
#include <QRegularExpression>

NetworkMonitor::NetworkMonitor(QObject *parent)
    : QObject(parent), totalBytesSent(0), totalBytesReceived(0), previousBytesSent(0), previousBytesReceived(0) {
    connect(&monitorTimer, &QTimer::timeout, this, &NetworkMonitor::onMonitoringTimeout);
}

void NetworkMonitor::startMonitoring() {
    if (!monitorTimer.isActive()) {
        monitorTimer.start(1000);
        NetworkLog log;
        log.setTimestamp(QDateTime::currentDateTime());
        log.setResponse("Monitoring started");
        log.setStatus("INFO");
        addLog(log);
    }
}

void NetworkMonitor::stopMonitoring() {
    if (monitorTimer.isActive()) {
        monitorTimer.stop();
        NetworkLog log;
        log.setTimestamp(QDateTime::currentDateTime());
        log.setResponse("Monitoring stopped");
        log.setStatus("INFO");
        addLog(log);
    }
}

void NetworkMonitor::addLog(const NetworkLog& log) {
    logs.append(log);
    emit logAdded(log);
    qDebug() << log.getTimestamp().toString(Qt::ISODate) << log.getResponse() << log.getStatus();
}

QVector<NetworkLog> NetworkMonitor::getLogs() const {
    return logs;
}

void NetworkMonitor::onMonitoringTimeout() {
    checkNetworkInterfaces();
    checkTcpConnections();
    checkUdpConnections();
    updateNetworkStats();
    detectNetworkErrors();
}

void NetworkMonitor::checkNetworkInterfaces() {
    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &interface : interfaces) {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            NetworkLog log;
            log.setTimestamp(QDateTime::currentDateTime());
            log.setServer("Interface up: " + interface.humanReadableName());
            log.setResponse("INFO");
            addLog(log);
        }
    }
}

void NetworkMonitor::checkTcpConnections() {
    QTcpSocket tcpSocket;
    tcpSocket.connectToHost("example.com", 80);
    if (tcpSocket.waitForConnected(1000)) {
        NetworkLog log;
        log.setTimestamp(QDateTime::currentDateTime());
        log.setResponse("TCP connection successful to example.com:80");
        log.setStatus("INFO");
        addLog(log);
        tcpSocket.disconnectFromHost();
    } else {
        NetworkLog log;
        log.setTimestamp(QDateTime::currentDateTime());
        log.setResponse("TCP connection failed to example.com:80");
        log.setStatus("ERROR");
        addLog(log);
    }
}

void NetworkMonitor::checkUdpConnections() {
    QUdpSocket udpSocket;
    QByteArray data("Test");
    udpSocket.writeDatagram(data, QHostAddress("example.com"), 12345);
    if (udpSocket.waitForBytesWritten(1000)) {
        NetworkLog log;
        log.setTimestamp(QDateTime::currentDateTime());
        log.setResponse("UDP datagram sent to example.com:12345");
        log.setStatus("INFO");
        addLog(log);
    } else {
        NetworkLog log;
        log.setTimestamp(QDateTime::currentDateTime());
        log.setResponse("UDP datagram failed to example.com:12345");
        log.setStatus("ERROR");
        addLog(log);
    }
}

void NetworkMonitor::updateNetworkStats() {
    qint64 bytesSent = 0;
    qint64 bytesReceived = 0;

    QFile file("/proc/net/dev");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.contains("eth0:")) {
                QStringList parts = line.split(QRegularExpression("\\s+"));
                if (parts.size() > 9) {
                    bytesReceived += parts[1].toLongLong();
                    bytesSent += parts[9].toLongLong();
                }
            }
        }
        file.close();
    }

    qint64 deltaBytesSent = bytesSent - previousBytesSent;
    qint64 deltaBytesReceived = bytesReceived - previousBytesReceived;

    NetworkLog sentLog;
    sentLog.setTimestamp(QDateTime::currentDateTime());
    sentLog.setResponse("Bytes sent: " + QString::number(deltaBytesSent));
    sentLog.setStatus("INFO");
    addLog(sentLog);

    NetworkLog receivedLog;
    receivedLog.setTimestamp(QDateTime::currentDateTime());
    receivedLog.setResponse("Bytes received: " + QString::number(deltaBytesReceived));
    receivedLog.setStatus("INFO");
    addLog(receivedLog);

    previousBytesSent = bytesSent;
    previousBytesReceived = bytesReceived;
}

void NetworkMonitor::detectNetworkErrors() {
    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &interface : interfaces) {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            NetworkLog log;
            log.setTimestamp(QDateTime::currentDateTime());
            log.setResponse("Simulated error detection on interface: " + interface.humanReadableName());
            log.setStatus("ERROR");
            addLog(log);
        }
    }
}
