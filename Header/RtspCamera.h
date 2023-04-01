#ifndef RTSPCAMERA_H
#define RTSPCAMERA_H

#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QVBoxLayout>
#include <QSslConfiguration>

class RtspCamera
{
public:
    RtspCamera();

    void initVideo();
    void connectVideo();
    // IP address need to be given with hand. Check Jetson ip address!
//    QString IPAdress = QString("rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4");

//    QString IPAdress = "http://192.168.0.18:8080/video/mjpeg";
//    QString IPAdress = "http://192.168.0.18:8080/video";

    QVBoxLayout *rtspLayout;
    QMediaPlayer *player;
    QNetworkRequest *networkHandler;
    QVideoWidget *videoWidget;

    bool m_running = false;

private:
    void showVideo();
};

#endif // RTSPCAMERA_H
