#include "mainwindow.h"
#include "myserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myServer mServer;

    MainWindow droneObserver;
    droneObserver.setWindowTitle("Drone Flight Observer");
    droneObserver.resize(1280, 720);
    droneObserver.show();

    return a.exec();
}
