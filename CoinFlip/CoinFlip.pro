#-------------------------------------------------
#
# Project created by QtCreator 2021-05-02T11:44:32
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoinFlip
TEMPLATE = app
CONFIG+=C++11

SOURCES += main.cpp\
        mainwindow.cpp \
    mypushbutton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS  += mainwindow.h \
    mypushbutton.h \
    chooselevelscene.h \
    playscene.h \
    mycoin.h \
    dataconfig.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
