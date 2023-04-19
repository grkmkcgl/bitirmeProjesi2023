#include "myserver.h"

myServer::myServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    // listen for new connection
    if(!server->listen(QHostAddress::Any, 1234))
    {
       qDebug() << "Server could not start...";
    }
    else
    {
       qDebug() << "Server started successfully!";
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
}

void myServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        sockets.removeOne(sender);
        qDebug() << "A user disconnected from server";
    }
}

void myServer::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());

    test += sender->bytesAvailable();
    qDebug() << "test value is: " << test;

    if (packetSize == -1)
    {
        packetSize = 0;
        packetSize -= (sender->bytesAvailable() - 4);
        buffer.append(sender->readAll());
        QByteArray packetSizeArr = buffer.mid(0,4);
        packetSize += packetSizeArr[0] << 24 & 0x00FFFFFFFF;
        packetSize += packetSizeArr[1] << 16 & 0x00FFFFFF;
        packetSize += packetSizeArr[2] << 8 & 0x00FFFF;
        packetSize += packetSizeArr[3] & 0x00FF;
        qDebug() << packetSize;
        buffer.remove(0,4);
    }
    else if(packetSize != 0)
    {
        packetSize -= sender->bytesAvailable();
        buffer.append(sender->readAll());
        qDebug() << packetSize;
    }

    if (packetSize == 0 || packetSize < 0)
    {
        tcpData = buffer;
        buffer.clear();
        packetSize = -1;
    }
    qDebug() << sender->bytesAvailable();
    qDebug() << "tcpData size: " << tcpData.size();


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
