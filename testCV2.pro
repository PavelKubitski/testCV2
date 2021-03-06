#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T11:08:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = testCV2
TEMPLATE = app
CONFIG += console



SOURCES += main.cpp\
        mainwindow.cpp \
    custspinbox.cpp \
    seed.cpp \
    ImageConverter.cpp \
    ColorSystemConverter.cpp \
    MorphologyOperation.cpp \
    ImageLabelForm.cpp \
    SVMclassifier.cpp \
    FeaturesCaculation.cpp \
    ChooseFeaturesWindow.cpp \
    TrainingDataDialog.cpp \
    MatDisplay.cpp \
    ROCDialog.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    custspinbox.h \
    seed.h \
    ImageConverter.h \
    ColorSystemConverter.h \
    MorphologyOperation.h \
    ImageLabelForm.h \
    SVMclassifier.h \
    FeaturesCaculation.h \
    ChooseFeaturesWindow.h \
    TrainingDataDialog.h \
    MatDisplay.h \
    ROCDialog.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    ImageLabelForm.ui \
    ChooseFeaturesWindow.ui \
    TrainingDataDialog.ui \
    ROCDialog.ui

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lopencv_highgui \
        -lopencv_core \
        -lopencv_video \
        -lopencv_imgproc \
        -lopencv_ml \

DISTFILES += \
    ../../../../Users/pavelkubitski/Desktop/Roc2/cppROC/roc.txt




