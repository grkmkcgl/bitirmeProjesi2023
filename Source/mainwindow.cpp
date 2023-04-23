#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // create and set camera widget
    auto videoFramelayout = new QVBoxLayout();
    videoFramelayout->addWidget(RtspCamera.videoWidget);
    ui->VideoFrame->setLayout(RtspCamera.rtspLayout);

    // image viewer
    imageLabel = new QLabel();
    imageLabel->setScaledContents(true);
    imageViewerLayout = new QVBoxLayout();
    imageViewerLayout->addWidget(imageLabel);
    ui->ImageViewer->setLayout(imageViewerLayout);

    // image iterator
    it = new QDirIterator("../../../treePhotos",
                       QStringList() << "*.jpg",
                       QDir::Files,
                       QDirIterator::Subdirectories);

    // init server
    tcpServer = new myServer;
    if (tcpServer->serverRunning == false)
    {
        ui->serverStatusLabel->setText("TCP Server couldn't start...");
        ui->serverStatusLabel->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->serverStatusLabel->setText("TCP Server started successfully!");
        ui->serverStatusLabel->setStyleSheet("QLabel { color : green; }");
    }

    // logo
    QPixmap logo("C:/Users/gorke/Desktop/QT/bitirmeProjesiArayuz/Resource/tubitak.png");
    ui->tubitakLabel->setScaledContents(true);
    ui->tubitakLabel->setPixmap(logo);

    connect(tcpServer, SIGNAL(menuConnectedSignal(bool)),
            this, SLOT(serverSignals(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_progressBar_valueChanged(int value)
{

}

void MainWindow::on_startVideoConnectionButton_clicked()
{
    RtspCamera.initVideo();
}

void MainWindow::on_ConnectVideoButton_clicked()
{
    RtspCamera.connectVideo();
}

void MainWindow::on_nextimagepushButton_clicked()
{
    if (!jpgList.isEmpty())
    {
        jpgListIndex += 1;
    }
    if ((jpgListIndex < jpgList.length()) && (!jpgList.isEmpty()))
    {
        image.load(jpgList[jpgListIndex]);
        imageLabel->setPixmap(image);
    }
    else
    {
        image.load(":/images/Resource/EOF.jpg");
        imageLabel->setPixmap(image);
    }
}

void MainWindow::on_previousimagepushButton_clicked()
{
    if (jpgListIndex > jpgList.length())
    {
        jpgListIndex = jpgList.length();
    }
    if (jpgListIndex > 0)
    {
        jpgListIndex -= 1;
        image.load(jpgList[jpgListIndex]);
        imageLabel->setPixmap(image);
    }
    else
    {
        jpgListIndex = -1;
        image.load(":/images/Resource/EOF.jpg");
        imageLabel->setPixmap(image);
    }
}

void MainWindow::on_tcpSocketPushButton_clicked()
{
    QByteArray valueToUi = tcpServer->tcpData;
    QPixmap tcpDataImage;
    tcpDataImage.loadFromData(valueToUi);
    imageLabel->setPixmap(tcpDataImage);
    heximageConverter::saveAsHex(tcpServer->tcpData);
    tcpServer->packetSize = -1; // reset packet size to take new input
}


void MainWindow::on_savedFilesPushButton_clicked()
{
    QDirIterator dir("../../treePhotos",
                   QStringList() << "*.jpg",
                   QDir::Files,
                   QDirIterator::Subdirectories);

    int newFiles = 0;
    while (dir.hasNext())
    {
        newFiles += 1;
        dir.next();
    }

    if (newFiles != jpgList.length())
    {
        delete it;
        it = new QDirIterator("../../treePhotos",
                           QStringList() << "*.jpg",
                           QDir::Files,
                           QDirIterator::Subdirectories);
        filesChanged = true;
        newFiles = 0;
        jpgList.clear();
    }

    while(it->hasNext() && filesChanged)
    {
        ui->statusbar->showMessage("Copying paths...");
        ui->statusbar->setStyleSheet("background-color: rgb(122, 0, 0);");
        jpgList.append(it->next());
    }
    filesChanged = false;

    jpgListIndex = jpgList.length() - 1;
    ui->statusbar->showMessage(QString("Done! Found %1 images.").arg(jpgList.length()));
    ui->statusbar->setStyleSheet("background-color: rgb(0, 255, 0);");
    image.load(jpgList[jpgListIndex]);
    imageLabel->setPixmap(image);
}

void MainWindow::serverSignals(bool user)
{
    if (user == true)
    {
        ui->serverStatusLabel->setText("A user connected");
    }
    else
        ui->serverStatusLabel->setText("A user disconnected");
}

