QT     += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Header/

VPATH   += \
    ./Source \
    ./Header \
    ./Form   \

SOURCES += \
    heximageConverter.cpp \
    main.cpp \
    camera.cpp \
    mainwindow.cpp \
    RtspCamera.cpp \
    myserver.cpp \


HEADERS += \
    TODO.h \
    camera.h \
    mainwindow.h \
    RtspCamera.h \
    myserver.h \
    heximageConverter.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
