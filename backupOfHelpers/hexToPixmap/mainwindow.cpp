#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = new QLabel();
    imageLabel->setScaledContents(true);
    imageViewerLayout = new QVBoxLayout();
    imageViewerLayout->addWidget(imageLabel);
    ui->ImageViewer->setLayout(imageViewerLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::converter()
{
//    // load image, save into arr, save image into arr as buffer
    QImage img_enrll("C:/Users/gorke/Desktop/QT/bitirmeProjesiArayuz/Resource/droneicon.png");
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    img_enrll.save(&buffer, "PNG");

//    // display image on ui
    QPixmap img;
    img.loadFromData(arr);
    imageLabel->setPixmap(img);

//    // create and write image as hex file
    QFile file("some_name.txt");
    file.open(QIODevice::WriteOnly);
    file.write(arr.toHex());
    file.close();

//    // load from txt file and show.
    QString filePath = "C:/Users/gorke/Desktop/QT/build-hexToPixmap-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/some_name.txt";
    QFile file(filePath);
    QByteArray test;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString hex = stream.readAll();
        test = QByteArray::fromHex(hex.toLatin1());
    }
    file.close();

    QPixmap img;
    img.loadFromData(test);
    imageLabel->setPixmap(img);
}

