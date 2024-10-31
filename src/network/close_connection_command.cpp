#include "../include/close_connection_command.h"
#include <QDebug>

CloseConnectionCommand::CloseConnectionCommand(std::shared_ptr<QTcpSocket> socket)
    : socket(socket) {}

void CloseConnectionCommand::execute()
{
    socket.get()->disconnectFromHost();
    if (socket.get()->state() == QAbstractSocket::UnconnectedState || socket.get()->waitForDisconnected(1000))
    {
        qDebug() << "Disconnected from host";
    }
    else
    {
        qDebug() << "Failed to disconnect from host";
    }
}
