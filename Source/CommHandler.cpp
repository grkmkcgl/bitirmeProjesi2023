#include "CommHandler.h"

CommHandler::CommHandler()
{
    commServer = new QTcpServer();   // initialize server
    serverIPAdress.setAddress(QHostAddress::LocalHost);   // take my PC's IP address
    qDebug() << "Communication server started with IP:" << serverIPAdress.toString();

    if(!commServer->listen(QHostAddress::Any, 25))  // listen for new connections from port 25
        qDebug() << "Server could not start...";
    else
    {
        qDebug() << "Server started successfully!";
    }
    connect(commServer, SIGNAL(newConnection()), this, SLOT(socketHandler()));
}

void CommHandler::socketHandler()
{
    // create and bind socket
    serverSocket = commServer->nextPendingConnection();

    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    serverSocket->write(QByteArray::fromStdString(serverSocket->peerAddress().toString().toStdString() + " connected to server!\n"));
    serverSocket->write("\r\nWelcome user\r\n220 OK\r\n");
    serverSocket->flush();
}

//void Server::onSocketStateChanged(QAbstractSocket::SocketState socketState)
//{
//    qDebug() << "socket state changed...";
//    if (socketState == QAbstractSocket::UnconnectedState)
//    {
//        qDebug() << "a user disconnected, closing socket...";
//        // some code about freeing space ...
//    }
//}

void CommHandler::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
//    serverSocket->waitForBytesWritten();
    QString toBuff = sender->readAll();
    if(!toBuff.compare("\010"))
    {
        buffer.chop(1);
        return;
    }
    buffer.append(toBuff);
    if(toBuff.contains("\r\n"))
    {
//        commandHandler(buffer);
        buffer = "";
    }
}

//void CommHandler::commandHandler(QString input)
//{
//    // change string type to handle substrings
//    std::string definedCString = input.toStdString();
//    int strLen = definedCString.length();

//    if(input.contains("HELO"))
//    {
//        if(!QString::compare(input, "HELO"))
//        {
//            serverSocket->write("Also need to enter client name!");
//            serverSocket->flush();
//            return;
//        }
//        serverSocket->write("250 Hello\r\n");
//        serverSocket->flush();
//    }
//    else if(input.contains("MAIL FROM"))
//    {
//        if(!QString::compare(input, "MAIL FROM"))
//        {
//            serverSocket->write("Need to specify mail!");
//            serverSocket->flush();
//            return;
//        }
//        std::string stdInput = definedCString.substr(10,strLen);
//        if(!mailrex.match(QString::fromStdString(stdInput)).hasMatch())
//        {
//            serverSocket->write("553 Invalid Sender Address");
//            serverSocket->flush();
//            return;
//        }
//        serverSocket->write("250 Sender OK\r\n");
//        serverSocket->flush();
//        mailFrom = stdInput;
//    }
//    else if(input.contains("RCPT TO"))
//    {
//        if(!QString::compare(input, "RCPT TO\r\n"))
//        {
//            serverSocket->write("Need to specify mail!");
//            serverSocket->flush();
//            return;
//        }
//        std::string stdInput = definedCString.substr(8,strLen);
//        if(!mailrex.match(QString::fromStdString(stdInput)).hasMatch())
//        {
//            serverSocket->write("553 Invalid Receipent Address");
//            serverSocket->flush();
//            return;
//        }
//        serverSocket->write("250 Receipent OK\r\n");
//        serverSocket->flush();
//        rcptTo = stdInput;
//    }
//    else if(input.contains("DATA"))
//    {
//        if(!QString::compare(input, "DATA"))
//        {
//            serverSocket->write("Enter your message!");
//            serverSocket->flush();
//            return;
//        }

//        std::string stdInput = definedCString.substr(5,strLen);
//        userMsg = stdInput;
//        fileHandler();
//    }
//    else if(input.contains("QUIT"))
//    {
//        serverSocket->write("221 OK\r\n");
//        serverSocket->flush();
//        serverSocket->close();
//    }
//    else { serverSocket->write("Invalid command\r\n"); serverSocket->flush(); }
//}
