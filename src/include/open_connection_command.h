#pragma once
#include "network_command.h"
#include <QTcpSocket>
#include <QString>
#include <memory>

class OpenConnectionCommand : public NetworkCommand {
public:
    OpenConnectionCommand(std::shared_ptr<QTcpSocket> socket, const QString &address, quint16 port);
    void execute() override;
    QString typeName() const override { return "OpenConnectionCommand"; }

private:
    std::shared_ptr<QTcpSocket> socket;
    QString address;
    quint16 port;
};
