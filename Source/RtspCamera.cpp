#include "RtspCamera.h"

RtspCamera::RtspCamera()
{
    rtspLayout = new QVBoxLayout();
    videoWidget = new QVideoWidget;
    rtspLayout->addWidget(videoWidget);
//    int frameWidth = ui->VideoFrame->width();
//    int frameHeight = ui->VideoFrame->height();
//    videoWidget->resize(frameWidth,frameHeight);
}

void RtspCamera::initVideo()
{
    if (m_running)
    {
        delete player;
        delete networkHandler;
        videoWidget->close();
    }
    m_running = true;
    videoWidget->show();
    player = new QMediaPlayer;
    networkHandler = new QNetworkRequest();
    QSslConfiguration sslConfig = networkHandler->sslConfiguration();
    sslConfig.setCaCertificates({});
    networkHandler->setSslConfiguration(sslConfig);
    this->showVideo();
}

void RtspCamera::connectVideo()
{
    // CRASHES APP DO NOT USE BUTTON
    delete player;
    delete networkHandler;
    this->showVideo();
}

void RtspCamera::showVideo()
{
    networkHandler->setUrl(QUrl(this->IPAdress));
    player->setMedia(*networkHandler);
    player->setVideoOutput(videoWidget);
    player->play();
    player->setVolume(0);
    qDebug()<< "error string: " << player->errorString() << Qt::endl
            << "connecting to ip:" << IPAdress;
}

