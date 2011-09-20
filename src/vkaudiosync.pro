#-------------------------------------------------
#
# Project created by QtCreator 2011-09-20T22:20:20
#
#-------------------------------------------------

QT       += core gui

TARGET = vkaudiosync
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    models/audiomodel.cpp \
    vkapi/vkapi.cpp

HEADERS  += mainwindow.h \
    models/audiomodel.h \
    vkapi/vkapi.h

FORMS    += mainwindow.ui
