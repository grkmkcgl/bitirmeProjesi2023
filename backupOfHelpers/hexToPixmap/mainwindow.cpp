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
    QImage img_enrll("C:/Users/gorke/Desktop/treePhotos/Red_Apple.jpg");
//    QImage img_enrll("C:/Users/gorke/Desktop/QT/bitirmeProjesiArayuz/Resource/droneicon.png");
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    img_enrll.save(&buffer, "JPG");   // when using yolo photos make it JPG

    QByteArray ba;
    QDataStream out(&ba, QIODevice::ReadWrite);
    out << arr;

//    // display image on ui
//    QPixmap img;
//    img.loadFromData(arr);
//    imageLabel->setPixmap(img);

//    // create and write image as hex file
    QFile fileSaver("some_name.txt");
    fileSaver.open(QIODevice::WriteOnly);
    fileSaver.write(ba);
    fileSaver.close();

//    // load from txt file and show.
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

    QPixmap img;
    img.loadFromData(test);
    imageLabel->setPixmap(img);

    bool iseq = (test == arr);
    qDebug() << iseq;
}

