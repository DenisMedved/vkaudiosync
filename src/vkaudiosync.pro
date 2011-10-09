#-------------------------------------------------
#
# Project created by QtCreator 2011-09-20T22:20:20
#
#-------------------------------------------------

QT       += core gui network webkit xml
TARGET = vkaudiosync
TEMPLATE = app
SOURCES += main.cpp\
    mainwindow.cpp \
    vk/provider.cpp \
    vk/audiofactory.cpp \
    vk/audiomodel.cpp \
    vk/profilemodel.cpp \
    vk/profilefactory.cpp
    #vk/audiomodel.cpp\
    #vk/config.cpp \
HEADERS  += mainwindow.h \
    vk/provider.h \
    vk/audiofactory.h \
    vk/audiomodel.h \
    vk/profilemodel.h \
    vk/profilefactory.h
    #vk/audiomodel.h
   #vk/config.h \

FORMS    += ui/mainwindow.ui

OTHER_FILES += \
    .gitignore
