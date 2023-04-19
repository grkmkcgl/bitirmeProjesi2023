#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow droneObserver;
    droneObserver.setWindowTitle("Drone Flight Observer");
    droneObserver.resize(1280, 720);
    droneObserver.show();

    return a.exec();
}
