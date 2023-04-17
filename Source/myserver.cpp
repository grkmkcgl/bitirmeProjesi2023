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
    socket->waitForBytesWritten(5000);

/*
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "test test test";


    QTcpSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);


    clientConnection->write(block);
    clientConnection->disconnectFromHost();
*/
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
    QByteArray datas = sender->readAll();
    qDebug() << datas;
    for (QTcpSocket* socket : sockets)
    {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
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
