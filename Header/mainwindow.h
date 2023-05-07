#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QDirIterator>
#include "RtspCamera.h"
#include "myserver.h"
#include "heximageConverter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    RtspCamera RtspCamera;

    // image viewer widget
    QPixmap image;
    QLabel *imageLabel = new QLabel();
    QVBoxLayout *imageViewerLayout = new QVBoxLayout();

    // file iterator to show images
//    QString imagesPath = "../../../treePhotos";
    QString imagesPath = "C:/Users/gorke/Desktop/QT/bitirmeProjesiArayuz/images";
    QDirIterator *it;
    QStringList jpgList;
    int jpgListIndex = -1;
    bool filesChanged = false;
    int imageFileNumber = 0;

    // init server
    myServer *tcpServer;

public slots:
    void serverSignals(bool);
    void imageTaken(bool);

private slots:
    void on_startVideoConnectionButton_clicked();
    void on_nextimagepushButton_clicked();
    void on_previousimagepushButton_clicked();
    void on_tcpSocketPushButton_clicked();
    void on_savedFilesPushButton_clicked();
    void on_sendMsgToDetectButton_clicked();
    void on_batteryBar_valueChanged(int value);

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
