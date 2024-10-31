#include "../include/udp_send_command.h"
#include <QDebug>

UdpSendCommand::UdpSendCommand(std::shared_ptr<QUdpSocket> socket, const QByteArray &data, const QHostAddress &address, quint16 port)
    : socket(socket), data(data), address(address), port(port) {}

void UdpSendCommand::execute() {
    socket->writeDatagram(data, address, port);
    if (socket->waitForBytesWritten(1000)) {
        qDebug() << "UDP datagram sent to" << address.toString() << ":" << port;
    } else {
        qDebug() << "Failed to send UDP datagram to" << address.toString() << ":" << port;
    }
}
