#  VKAudioSync
#  Copyright (C) 2011 Denis Medved <thebucefal@gmail.com>
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
QT += \
	webkit \
	network \
	xml

TEMPLATE = app

TARGET = vkaudiosync

DESTDIR = bin

MOC_DIR = build

OBJECTS_DIR = build

TRANSLATIONS += \
	src/translations/main_en.ts \
	src/translations/main_ru.ts

RESOURCES += \
	src/icons.qrc

HEADERS += \
	src/audioitemdelegate.h \
	src/audiolistmodel.h \
	src/mainwindow.h \
	src/appsettings.h \
	src/synchservice.h \
	src/downloadthread.h \
	src/audioitem.cpp \
	src/vk/vkservice.h \
	src/profilemodel.h \
	src/about.h \
	src/appcookiejar.h \
	src/audiolistview.h

FORMS += \
	src/ui/mainwindow.ui \
	src/ui/about.ui

SOURCES += \
	src/audioitemdelegate.cpp \
	src/audiolistmodel.cpp \
	src/main.cpp \
	src/mainwindow.cpp \
	src/appsettings.cpp \
	src/synchservice.cpp \
	src/downloadthread.cpp \
	src/audioitem.cpp \
	src/vk/vkservice.cpp \
	src/profilemodel.cpp \
	src/about.cpp \
	src/appcookiejar.cpp \
	src/audiolistview.cpp


OTHER_FILES += \
	src/share/applications/vkaudiosync.desktop \
	README \
	AUTHORS \
	.gitignore

unix {
	target.path = /usr/bin

	applications.path = /usr/share/applications
	applications.files = src/share/applications/vkaudiosync.desktop

	icons.path = /usr/share/icons/hicolor/64x64/apps
	icons.files = src/share/icons/hicolor/64x64/apps/*

	data.path = /usr/share/vkaudiosync
	data.files = src/share/vkaudiosync/*

	INSTALLS += target applications icons data
}

