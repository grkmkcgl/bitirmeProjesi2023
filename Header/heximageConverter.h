#ifndef HEXIMAGECONVERTER_H
#define HEXIMAGECONVERTER_H

#include <QFile>
#include <QBuffer>
#include <QDebug>
#include <QImage>
#include <QPixmap>

class heximageConverter
{
public:
    heximageConverter();

    static void converter(QByteArray);
};

#endif // HEXIMAGECONVERTER_H
