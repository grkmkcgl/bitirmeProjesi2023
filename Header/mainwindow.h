#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include "RtspCamera.h"

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

    // image viewer
//    QPixmap image("C:/Users/gorke/Desktop/treePhotos/Red_Apple.jpg");
    QPixmap image;
    QLabel *imageLabel = new QLabel();
    QVBoxLayout *imageViewerLayout = new QVBoxLayout();

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
