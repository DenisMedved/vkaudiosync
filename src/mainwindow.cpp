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

#include  <QWidget>
#include  <QTextEdit>
#include <QApplication>
#include  <QVBoxLayout>
#include <QDesktopWidget>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vk/provider.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	m_pushButton = new QPushButton(this);
	m_vBoxLayout = new QVBoxLayout;
	m_buttonGetAudioList = new QPushButton(this);
	m_centralWidget = new QWidget(this);
	m_buttonExit = new QPushButton(this);

	int desktopWidth = QApplication::desktop()->width();
	int desktoHeight = QApplication::desktop()->height();

	resize(300,80);
	move((desktopWidth-width()) / 2 , (desktoHeight - height()) / 3);

	m_vBoxLayout->addWidget(m_pushButton);
	m_vBoxLayout->addWidget(m_buttonGetAudioList);
	m_vBoxLayout->addWidget(m_buttonExit);

	m_centralWidget->setLayout(m_vBoxLayout);
	setCentralWidget(m_centralWidget);

	m_vkProvider = new VK::Provider(this);

	m_pushButton->setText("Authorize");
	m_buttonGetAudioList->setText("Get audio list");
	m_buttonExit->setText("Exit");

	connect(m_pushButton, SIGNAL(clicked(bool)),
		this, SLOT(getToken()));
	connect(m_buttonGetAudioList,SIGNAL(clicked(bool)),
		this, SLOT(getAudioList()));
	connect(m_buttonExit, SIGNAL(clicked(bool)),
		this, SLOT(slotCloseApplication())
		);
}

MainWindow::~MainWindow()
{
	delete m_pushButton;
	delete ui;
	delete m_vkProvider;
}

void MainWindow::getToken()
{
	m_vkProvider->login();
}

void MainWindow::getAudioList()
{
	m_vkProvider->getAudioList();
}

void MainWindow::slotCloseApplication()
{
	QApplication::exit();
}

void MainWindow::setSettings(QSettings *settings)
{
	m_settings = settings;
	m_vkProvider->setSettings(settings);
}

QSettings* MainWindow::getSettings()
{
	return m_settings;
}
