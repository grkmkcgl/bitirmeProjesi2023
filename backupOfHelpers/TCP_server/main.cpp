#include "serverwindow.h"
#include "myserver.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myServer mServer;

//    ServerWindow w;
//    w.show();
//    w.setWindowTitle("LIBVLC TEST");
    return a.exec();
}
