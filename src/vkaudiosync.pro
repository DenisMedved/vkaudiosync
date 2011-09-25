#-------------------------------------------------
#
# Project created by QtCreator 2011-09-20T22:20:20
#
#-------------------------------------------------

QT       += core gui network webkit
TARGET = vkaudiosync
TEMPLATE = app
SOURCES += main.cpp\
    mainwindow.cpp\
    models/vkmodel.cpp
    #models/audiomodel.cpp\
    #models/config.cpp \
HEADERS  += mainwindow.h\
   models/vkmodel.h
    #models/audiomodel.h
   #models/config.h \


FORMS    += ui/mainwindow.ui
