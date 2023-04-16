#include "myserver.h"
#include <QDataStream>
#include <QThread>

myServer::myServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    qDebug() << "server address: " <<server->serverAddress();

    // listen for new connection
    if(!server->listen(QHostAddress::Any, 1234))
    {
       qDebug() << "Server could not start...";
    }
    else
    {
       qDebug() << QHostAddress::Any;
       qDebug() << "Server started successfully!";
    }

    qDebug() << server->socketDescriptor();
//    qDebug() << QNetworkInterface::allAddresses();
}


void myServer::onNewConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    socket->write("hello \r\n");
    socket->flush(); // to buffer (or from buffer)
    socket->waitForBytesWritten(5000);

    sockets.push_back(socket);
    for (QTcpSocket* socket : sockets)
    {
        socket->write(QByteArray::fromStdString(socket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }


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
