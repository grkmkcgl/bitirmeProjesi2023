#include "myserver.h"
#include "ui_mainwindow.h"

myServer::myServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    // listen for new connection
    if(!server->listen(QHostAddress::Any, 1234))
    {
       serverRunning = false;
    }
    else
    {
       serverRunning = true;
    }

//    qDebug() << QNetworkInterface::allAddresses();
}


void myServer::onNewConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    sockets.push_back(socket);
    for (QTcpSocket* socket : sockets)
    {
        socket->write(QByteArray::fromStdString(socket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }

    qDebug() << "A user is connected";
    socket->write("hello \r\n");
    socket->flush(); // to buffer (or from buffer)
    socket->waitForBytesWritten(100);
    emit menuConnectedSignal(true);
}

void myServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        sockets.removeOne(sender);
        qDebug() << "A user disconnected from server";
        emit menuConnectedSignal(false);
    }
}

void myServer::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    if (packetSize == -1)
    {
        int test = 0;
        packetSize = 0;
        packetSize -= (sender->bytesAvailable() - 4);
        buffer.append(sender->readAll());
        QByteArray packetSizeArr = buffer.mid(0,4);
        packetSize += packetSizeArr[0] << 24 & 0x00FFFFFFFF;
        test += packetSizeArr[0] << 24 & 0x00FFFFFFFF;
        packetSize += packetSizeArr[1] << 16 & 0x00FFFFFF;
        test += packetSizeArr[1] << 16 & 0x00FFFFFF;
        packetSize += packetSizeArr[2] << 8 & 0x00FFFF;
        test += packetSizeArr[2] << 8 & 0x00FFFF;
        packetSize += packetSizeArr[3] & 0x00FF;
        test += packetSizeArr[3] & 0x00FF;
        qDebug() << "packetSize: " << packetSize << "whole packet: " << test;
        buffer.remove(0,4);  // remove header
    }
    else if(packetSize != 0)
    {
        packetSize -= sender->bytesAvailable();
        buffer.append(sender->readAll());
        qDebug() << "packetSize: " << packetSize;
    }

    if (packetSize == 0 || packetSize < 0)
    {
        tcpData = buffer;
        buffer.clear();
        packetSize = -1;
    }
    qDebug() << "tcpData size: " << tcpData.size();

    // idk what this is
    for (QTcpSocket* socket : sockets)
    {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + tcpData.toStdString()));
    }
}

void myServer::sendSomething()
{

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "test test test";


    QTcpSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);


    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}
