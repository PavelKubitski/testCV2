#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T11:08:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testCV2
TEMPLATE = app
CONFIG += console



SOURCES += main.cpp\
        mainwindow.cpp \
    custspinbox.cpp \
    seed.cpp \
    ImageConverter.cpp \
    ColorSystemConverter.cpp

HEADERS  += mainwindow.h \
    custspinbox.h \
    seed.h \
    ImageConverter.h \
    ColorSystemConverter.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lopencv_highgui \
        -lopencv_core \
        -lopencv_video \
        -lopencv_imgproc \




