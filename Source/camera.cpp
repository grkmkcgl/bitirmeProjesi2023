#include "camera.h"
#include "qglobal.h"

#include <QActionGroup>

Camera::Camera()
{
    // camera ayarlamak için bazı şeyler burada, bazıları mainwindow.cpp'de

//    camera_view = new QCameraViewfinder();  // camera capture is here
//    setup_camera_devices();

    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras)
        qDebug() << cameraInfo.deviceName();

    QCameraViewfinderSettings mySettings;
    mySettings.setResolution(640,480);

//    camera = new QCamera("@device:pnp:\\\\?\\usb#vid_32e4&pid_0415&mi_00#8&1d2fe1d2&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global");
    camera = new QCamera();
    vidWig = new QVideoWidget();
    layout = new QVBoxLayout();
    layout->addWidget(vidWig);
    camera->setViewfinder(vidWig);
    camera->setViewfinderSettings(mySettings);
    camera->start();

    // AŞAĞIDAKİ KOD ÇALIŞIYOR
    QList support = camera->supportedViewfinderFrameRateRanges();
//    support[0].maximumFrameRate;  // böyle kullanılıyor
    for(int i = 0; i < support.size(); i++)
        qDebug() << support[i].maximumFrameRate;

}

void Camera::set_camera_action(QAction *camera_action)
{

}

void Camera::set_camera(const QCameraInfo &camera_info)
{

}

void Camera::setup_camera_devices()
{

}

