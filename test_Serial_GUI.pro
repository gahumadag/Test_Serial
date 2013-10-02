#-------------------------------------------------
#
# Project created by QtCreator 2013-09-30T18:20:07
#
#-------------------------------------------------

QT       += core gui

TARGET = test_Serial_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connection.cpp

HEADERS  += mainwindow.h \
    arduino-serial.hpp \
    connection.h

FORMS    += mainwindow.ui
