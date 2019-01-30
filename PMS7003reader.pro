#-------------------------------------------------
#
# Project created by QtCreator 2019-01-26T09:05:17
#
#-------------------------------------------------

QT += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PMS7003reader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    pms7003.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    pms7003.h

FORMS    += mainwindow.ui
