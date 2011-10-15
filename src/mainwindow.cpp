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
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vk/provider.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	int desktopWidth = QApplication::desktop()->width();
	int desktoHeight = QApplication::desktop()->height();

	move((desktopWidth-width()) / 2 , (desktoHeight - height()) / 3);

	m_vkProvider = new VK::Provider(this);
	m_synch = new Synch::Synchronizer(this);

	connect(m_vkProvider,SIGNAL(modelsChanged(QList<VK::AudioModel>*)),
		this,SLOT(slotAudioModelChanged(QList<VK::AudioModel>*)));
	connect(ui->synchBtn, SIGNAL(clicked()),
		this, SLOT(slotSynh())); //TODO: rename method
	connect(ui->dirBtn, SIGNAL(clicked()),
		this, SLOT(slotSelectDirectory())); //TODO: rename method
	m_vkProvider->login();

}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_vkProvider;
	delete m_synch;
}

void MainWindow::setSettings(QSettings *settings)
{
	m_settings = settings;
	m_vkProvider->setSettings(settings);
	m_synch->setSettings(settings);
}

QSettings* MainWindow::getSettings()
{
	return m_settings;
}

void MainWindow::slotSelectDirectory()
{
	QString dir = QFileDialog::getExistingDirectory(this, "Synch with...","", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	setDir(QDir(dir));
}

 void MainWindow::setDir(QDir dir)
 {
	 m_synch->setDir(dir);
 }

  void MainWindow::slotAudioModelChanged(QList<VK::AudioModel> *list)
  {
	  m_synch->setAudioList(list);
  }

  void MainWindow::slotSynh()
  {
	  m_synch->synchronize();
  }

  void MainWindow::slotLoginSuccess()
  {
	  show();
  }

  void MainWindow::slotLoginUnsuccess()
  {
	  QApplication::exit();
  }
