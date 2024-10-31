#include "../include/receive_data_command.h"

ReceiveDataCommand::ReceiveDataCommand(std::shared_ptr<QTcpSocket> socket) : socket(socket) {}

void ReceiveDataCommand::execute() {
    if (socket->waitForReadyRead()) {
        receivedData = socket->readAll();
        qDebug() << "Data received:" << receivedData;
    } else {
        qDebug() << "No data received!";
    }
}

QString ReceiveDataCommand::getReceivedData() const {
    return QString::fromUtf8(receivedData.toStdString());
}
