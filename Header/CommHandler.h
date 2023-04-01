#ifndef COMMHANDLER_H
#define COMMHANDLER_H

#include <QTcpServer>
#include <QTcpSocket>

class CommHandler : public QObject
{
    Q_OBJECT

public:
    CommHandler();
    virtual ~CommHandler() { delete this; };

    QHostAddress serverIPAdress;
    QString buffer;

    std::string userMsg;

    void commandHandler(QString);
    void fileHandler();

public slots:
    void onReadyRead();
    void socketHandler();                 // for new connections

private:
    QTcpServer *commServer;
    QTcpSocket *serverSocket;

};

#endif // COMMHANDLER_H
