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
    vkapi/vkapi.cpp \
    models/config.cpp \
    directorysync.cpp

HEADERS  += mainwindow.h \
    models/audiomodel.h \
    vkapi/vkapi.h \
    models/config.h \
    directorysync.h

FORMS    += mainwindow.ui
