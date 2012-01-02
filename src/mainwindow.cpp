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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	//setup ui
	ui->setupUi(this);

	//setup model delegate serice and settings
	m_pAppSettings = new AppSettings(this);
	m_pVkService = new VK::VKService(this);
	m_pAudioModel = new AudioListModel(this);
	m_pAudioItemDelegate = new AudioItemDelegate(this);
	m_pSynchService = new SynchService(this);


	//setup model and delerator for audio list view
	ui->listView->setItemDelegate(m_pAudioItemDelegate);
	ui->listView->setModel(m_pAudioModel);

	//move vindow to center top
	int desktopWidth = QApplication::desktop()->width();
	int desktoHeight = QApplication::desktop()->height();
	move((desktopWidth-width()) / 2 , (desktoHeight - height()) / 3);

	//load configuration file and create if not exist
	m_pAppSettings->load();
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_pAppSettings;
	delete m_pVkService;
	delete m_pAudioModel;
	delete m_pAudioItemDelegate;
	delete m_pSynchService;
}

