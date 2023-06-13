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
    int noOfApples = 0;
    int noOfTrees = 0;
    int wholeData = 0;
    int packetSize = -1;
    bool serverRunning = false;

    QTcpServer *server;

signals:
    bool menuConnectedSignal(bool);
    bool imageTaken(bool);

public slots:
    void onNewConnection();
    void onReadyRead();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void sendMessage(QString);

private:
    QList<QTcpSocket*>  sockets;

};

#endif // MYSERVER_H
