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


