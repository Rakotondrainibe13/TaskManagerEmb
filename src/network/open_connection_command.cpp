#include "../include/open_connection_command.h"
#include <QDebug>

OpenConnectionCommand::OpenConnectionCommand(std::shared_ptr<QTcpSocket> socket, const QString &address, quint16 port)
    : socket(socket), address(address), port(port)
{
}

void OpenConnectionCommand::execute()
{
    socket->connectToHost(address, port);
    if (socket->waitForConnected(1000))
    {
        qDebug() << "Connected to" << address << ":" << port;
    }
    else
    {
        qDebug() << "Failed to connect to" << address << ":" << port;
    }
}
