#pragma once
#include "network_command.h"
#include <QUdpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <memory>

class UdpSendCommand : public NetworkCommand {
public:
    UdpSendCommand(std::shared_ptr<QUdpSocket> socket, const QByteArray &data, const QHostAddress &address, quint16 port);
    void execute() override;
    QString typeName() const override { return "UdpSendCommand"; }

private:
    std::shared_ptr<QUdpSocket> socket;
    QByteArray data;
    QHostAddress address;
    quint16 port;
};
