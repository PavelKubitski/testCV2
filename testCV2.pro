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
    converter.cpp \
    custspinbox.cpp \
    seed.cpp

HEADERS  += mainwindow.h \
    converter.h \
    custspinbox.h \
    seed.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lopencv_highgui \
        -lopencv_core \
        -lopencv_video \
        -lopencv_imgproc \




