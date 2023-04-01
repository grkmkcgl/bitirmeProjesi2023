#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QScopedPointer>
#include <QAction>
#include <QCameraViewfinder>
#include <QVideoWidget>

#include <QBoxLayout>

class Camera
{
public:
    Camera();

    void set_camera_action(QAction *camera_action);
    void set_camera(const QCameraInfo &camera_info);

    void setup_camera_devices();

//    QScopedPointer<QCamera> camera;
//    QCameraViewfinder *camera_view;

    QCamera *camera;
    QVideoWidget *vidWig;
    QVBoxLayout *layout;
};

#endif // CAMERA_H
