#include "heximageConverter.h"

heximageConverter::heximageConverter()
{

}

void heximageConverter::saveAsHex(QByteArray tcpArr)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::ReadWrite);
    out << tcpArr;

    QFile fileSaver("test.txt");
    fileSaver.open(QIODevice::WriteOnly);
    fileSaver.write(buffer);
    fileSaver.close();
}

void heximageConverter::hexToPixmap(QByteArray valueFromSocket)
{
    // load from txt file and show.
    QFile file("some_name.txt");
    QByteArray test;

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "couldn't open file!";
        return;
    }
    QDataStream stream(&file);
    stream >> test;
    file.close();

      // display image on ui
//    QPixmap img;
//    img.loadFromData(test);
//    imageLabel->setPixmap(img);


      // datastream input can be used with deleting headers:
//    QByteArray sil = file.readAll();
//    sil.remove(0,4);
//    QPixmap img;
//    img.loadFromData(sil);
//    imageLabel->setPixmap(img);

    // for debug purposes
//    bool iseq = (test == arr);
//    if (iseq) qDebug() << "input and readed output file is equal, image should be loadable.";
//    else qDebug() << "something wrong";
}
