#include "../include/send_data_command.h"
#include <QDebug>

SendDataCommand::SendDataCommand(std::shared_ptr<QTcpSocket> socket, const QByteArray &data)
    : socket(socket), data(data) {}

void SendDataCommand::execute() {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data);
        if (socket->waitForBytesWritten(1000)) {
            qDebug() << "Data sent:" << data;
        } else {
            qDebug() << "Failed to send data:" << data;
        }
    } else {
        qDebug() << "Socket is not connected";
    }
}
