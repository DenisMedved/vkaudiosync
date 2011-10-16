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
    vk/profilefactory.cpp \
    sync/synchronizer.cpp \
    audioitemdelegate.cpp \
    audiolistmodel.cpp
HEADERS  += mainwindow.h \
    vk/provider.h \
    vk/audiofactory.h \
    vk/audiomodel.h \
    vk/profilemodel.h \
    vk/profilefactory.h \
    sync/synchronizer.h \
    audioitemdelegate.h \
    audiolistmodel.h
FORMS    += ui/mainwindow.ui
OTHER_FILES += \
    .gitignore\
   AUTHORS\
   LICENSE\
   README
