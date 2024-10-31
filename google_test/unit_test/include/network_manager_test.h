#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../src/include/open_connection_command.h"
#include "../../../src/include/send_data_command.h"
#include "../../../src/include/close_connection_command.h"
#include "../../../src/include/udp_send_command.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

class NetworkManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        mockServer = new QTcpServer();
        ASSERT_TRUE(mockServer->listen(QHostAddress::LocalHost, 12345));
    }

    void TearDown() override {
        delete mockServer;
    }

    QTcpServer* mockServer;
};

TEST_F(NetworkManagerTest, ExecuteOpensConnection) {

    auto socket = std::make_shared<QTcpSocket>();
    OpenConnectionCommand command(socket, "127.0.0.1", 12345);
    
    command.execute();
    
    ASSERT_EQ(socket->state(), QAbstractSocket::ConnectedState);
    
}

TEST_F(NetworkManagerTest, ExecuteSendsData) {

    auto socket = std::make_shared<QTcpSocket>();
    socket->connectToHost("127.0.0.1", 12345);
    QByteArray data("Hello, World!");
    SendDataCommand command(socket, data);
    
    command.execute();
    
    ASSERT_EQ(socket->bytesToWrite(), 0); 
}

TEST_F(NetworkManagerTest, ExecuteClosesConnection) {
    auto socket = std::make_shared<QTcpSocket>();
    socket->connectToHost("127.0.0.1", 12345);
    CloseConnectionCommand command(socket);
    
    command.execute();
    
    ASSERT_EQ(socket->state(), QAbstractSocket::UnconnectedState);
}

TEST_F(NetworkManagerTest, ExecuteSendsUdpData) {
    QUdpSocket receiverSocket;
    ASSERT_TRUE(receiverSocket.bind(QHostAddress::LocalHost, 12345));
    
    auto socket = std::make_shared<QUdpSocket>();
    QByteArray data("Hello, UDP!");
    QHostAddress address("127.0.0.1");
    quint16 port = 12345;
    UdpSendCommand command(socket, data, address, port);
    
    command.execute();
    
    ASSERT_TRUE(receiverSocket.waitForReadyRead(1000)); 
    QByteArray receivedData;
    QHostAddress sender;
    quint16 senderPort;
    receivedData.resize(receiverSocket.pendingDatagramSize());
    receiverSocket.readDatagram(receivedData.data(), receivedData.size(), &sender, &senderPort);

    ASSERT_EQ(receivedData, data); 
}

