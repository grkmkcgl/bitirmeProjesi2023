#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QDirIterator>
#include "RtspCamera.h"
#include "myserver.h"

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
    QDirIterator *it;
    QStringList jpgList;
    int jpgListIndex = -1;
    bool filesChanged = false;

    // init server
    myServer *tcpServer;

private slots:
    void on_progressBar_valueChanged(int value);
    void on_startVideoConnectionButton_clicked();
    void on_ConnectVideoButton_clicked();
    void on_nextimagepushButton_clicked();
    void on_previousimagepushButton_clicked();
    void on_autoChangePushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
