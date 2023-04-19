#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QThread>

class myServer : public QObject
{
    Q_OBJECT
public:
    explicit myServer(QObject *parent = nullptr);
    QByteArray tcpData;  // readed socket data kept here
    QByteArray buffer;
    int packetSize = -1;
    int test = 0;

signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void sendSomething();

private:
    QTcpServer *server;
    QList<QTcpSocket*>  sockets;

};

#endif // MYSERVER_H
