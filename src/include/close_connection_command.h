#pragma once
#include "network_command.h"
#include <QTcpSocket>
#include <memory>

class CloseConnectionCommand : public NetworkCommand {
public:
    CloseConnectionCommand(std::shared_ptr<QTcpSocket> socket);
    void execute() override;
    QString typeName() const override { return "CloseConnectionCommand"; }

private:
    std::shared_ptr<QTcpSocket> socket;
};
