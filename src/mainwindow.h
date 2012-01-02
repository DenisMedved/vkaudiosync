/*
  *  VKAudioSync
  *  Copyright (C) 2011 Denis Medved <thebucefal@gmail.com>
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include <appsettings.h>
#include <vk/vkservice.h>
#include <synchservice.h>

//use in impl.
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "audiolistmodel.h"
#include "audioitemdelegate.h"

namespace Ui
{
	class MainWindow;
}

namespace VK
{
	class MainWindow;
}

namespace Synch
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow *ui;
	VK::VKService *m_pVkService;
	AudioListModel *m_pAudioModel;
	AudioItemDelegate *m_pAudioItemDelegate;
	AppSettings *m_pAppSettings;
	SynchService *m_pSynchService;

private slots:

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

 public slots:
};


#endif // MAINWINDOW_H
