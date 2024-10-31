#pragma once
#include <QTcpSocket>
#include <QString>
#include <memory>
#include "network_command.h"

class ReceiveDataCommand : public NetworkCommand {

public:
    ReceiveDataCommand(std::shared_ptr<QTcpSocket> socket);
    void execute() override;
    QString getReceivedData() const;
    QString typeName() const override { return "ReceiveDataCommand"; }

private:
    std::shared_ptr<QTcpSocket> socket;
    QByteArray receivedData;
};
