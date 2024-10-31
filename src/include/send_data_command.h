#pragma once
#include "network_command.h"
#include <QTcpSocket>
#include <QByteArray>
#include <memory>

class SendDataCommand : public NetworkCommand {
public:
    SendDataCommand(std::shared_ptr<QTcpSocket> socket, const QByteArray &data);
    void execute() override;
    QString typeName() const override { return "SendDataCommand"; }

private:
    std::shared_ptr<QTcpSocket> socket;
    QByteArray data;
};
