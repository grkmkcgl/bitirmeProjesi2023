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
//    QPixmap image("C:/Users/gorke/Desktop/treePhotos/Red_Apple.jpg");
    imageLabel = new QLabel();
    imageLabel->setScaledContents(true);
//    imageLabel->setPixmap(image);

    imageViewerLayout = new QVBoxLayout();
    imageViewerLayout->addWidget(imageLabel);
    ui->ImageViewer->setLayout(imageViewerLayout);

    it = new QDirIterator("C:/Users/gorke/Desktop/treePhotos",
                       QStringList() << "*.jpg",
                       QDir::Files,
                       QDirIterator::Subdirectories);


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

#include <QDirIterator>
#include <QThread>
void MainWindow::on_nextimagepushButton_clicked()
{
    if(it->hasNext())
    {
//        QThread::msleep(1000);
//        qDebug() << it->next();
        image.load(it->next());
        imageLabel->setPixmap(image);
    }
    else
    {
        // does delete needed here?????
        imageLabel->clear();
        it = new QDirIterator("C:/Users/gorke/Desktop/treePhotos",
                              QStringList() << "*.jpg",
                              QDir::NoFilter,
                              QDirIterator::Subdirectories);
        qDebug() << "no more files in directory";
    }
}

void MainWindow::on_previousimagepushButton_clicked()
{

}

void MainWindow::on_autoChangePushButton_clicked()
{

}

