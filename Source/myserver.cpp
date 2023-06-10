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

    qDebug() << QNetworkInterface::allAddresses();
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
//        qDebug() << "A user disconnected from server";
        emit menuConnectedSignal(false);
    }
}

void myServer::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    if (packetSize == -1)
    {
        wholeData = 0;
        packetSize = 0;
        packetSize -= (sender->bytesAvailable() - 4);
        buffer.append(sender->readAll());
        QByteArray packetSizeArr = buffer.mid(0,4);
        packetSize += packetSizeArr[0] << 24 & 0x00FFFFFFFF;
        wholeData += packetSizeArr[0] << 24 & 0x00FFFFFFFF;
        packetSize += packetSizeArr[1] << 16 & 0x00FFFFFF;
        wholeData += packetSizeArr[1] << 16 & 0x00FFFFFF;
        packetSize += packetSizeArr[2] << 8 & 0x00FFFF;
        wholeData += packetSizeArr[2] << 8 & 0x00FFFF;
        packetSize += packetSizeArr[3] & 0x00FF;
        wholeData += packetSizeArr[3] & 0x00FF;
//        qDebug() << "packetSize: " << packetSize << "whole packet: " << wholeData;
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
        tcpData = buffer.left(wholeData);
        QByteArray noOfApplesArr = buffer.right(4);
        QDataStream ds(noOfApplesArr);
        int newNoOfApples;
        ds >> newNoOfApples;
        noOfApples += newNoOfApples;
        buffer.clear();
        packetSize = -1;
        emit imageTaken(true);
    }
    qDebug() << "tcpData size: " << tcpData.size();

    // idk what this is
    for (QTcpSocket* socket : sockets)
    {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + tcpData.toStdString()));
    }
}

void myServer::sendMessage(QString msg)
{
    QByteArray myMsg = msg.toUtf8();

    for (QTcpSocket* socket : sockets)
    {
        socket->write(myMsg);
        socket->flush();
        socket->waitForBytesWritten(10);
    }
//    QTcpSocket *clientConnection = server->nextPendingConnection();
//    connect(clientConnection, &QAbstractSocket::disconnected,
//            clientConnection, &QObject::deleteLater);
//    clientConnection->write(block);
}
