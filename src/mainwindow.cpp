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

MainWindow::MainWindow(QWidget *parent /*=0*/) :
	QMainWindow(parent)
{
	//setup ui
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	m_pAbout = new About(this);

	//setup model delegate serice and settings
	m_pAppSettings = new AppSettings(this);
	m_pVkService = new VK::VKService(this);
	m_pAudioModel = new AudioListModel(this);
	m_pAudioItemDelegate = new AudioItemDelegate(this);
	m_pSynchService = new SynchService(this);
	m_pProfileModel = new ProfileModel;

	m_pSynchService->setAudioModel(m_pAudioModel);

	//setup model and delerator for audio list view
	ui->listView->setItemDelegate(m_pAudioItemDelegate);
	ui->listView->setModel(m_pAudioModel);

	//move vindow to center top
	int desktopWidth = QApplication::desktop()->width();
	int desktoHeight = QApplication::desktop()->height();
	move((desktopWidth-width()) / 2 , (desktoHeight - height()) / 3);

	//load configuration file and create if not exist
	m_pAppSettings->load();

	m_logined = false;

	// connects
	// UI
	connect(ui->allowUpload, SIGNAL(clicked(bool)),
			this,SLOT(slotAllowUpload(bool))
	);
	connect(ui->autoLogin, SIGNAL(clicked(bool)),
			this,SLOT(slotAutoLogin(bool))
	);
	connect(ui->loginButton, SIGNAL(clicked()),
				this,SLOT(slotLoginLogaut())
	);
	connect(ui->selectButton, SIGNAL(clicked()),
			this,SLOT(slotChooseDir())
	);
	connect(ui->syncButton, SIGNAL(clicked()),
			this,SLOT(slotStartSynch())
	);
	connect(ui->settingsButton, SIGNAL(clicked()),
			this,SLOT(slotSettings())
	);
	connect(ui->aboutButton,SIGNAL(clicked()),
			this,SLOT(slotAbout())
	);
	connect(ui->exitButton,SIGNAL(clicked()),
			this,SLOT(slotExit())
	);
	//VK SERVICE
	connect(m_pVkService,SIGNAL(loginSuccess(const QByteArray)),
			this,SLOT(slotLoginSuccess(QByteArray))
	);
	connect(m_pVkService,SIGNAL(audioListLoaded(const QByteArray)),
			this,SLOT(slotAudioListLoaded(QByteArray))
	);
	connect(m_pVkService,SIGNAL(profileLoaded(const QByteArray)),
			this,SLOT(slotProfileLoaded(QByteArray))
	);
	connect(m_pVkService,SIGNAL(loginUnsuccess()),
			this,SLOT(slotLoginUnsuccess())
	);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_pAppSettings;
	delete m_pVkService;
	delete m_pAudioModel;
	delete m_pAudioItemDelegate;
	delete m_pSynchService;
	delete m_pProfileModel;
}

void MainWindow::runSynch()
{
	m_pSynchService->setThreadsCount(5); //TODO: load from some config
	m_pSynchService->synchronize();
}

void MainWindow::slotAllowUpload(bool allow)
{
	QMessageBox::information(this,"Not work","temporary not work");
}

void MainWindow::slotAutoLogin(bool allow)
{
	QMessageBox::information(this,"Not work","temporary not work");
}

void MainWindow::slotLoginLogaut()
{
	if (m_logined) {
		//mk logaut
	} else {
		ui->loginButton->setText(tr("Logout"));
		m_pVkService->login();
	}
}

void MainWindow::slotChooseDir()
{

}

void MainWindow::slotStartSynch()
{

}

void MainWindow::slotSettings()
{
	QMessageBox::information(this,"Not work","temporary not work");
}

void MainWindow::slotAbout()
{
	m_pAbout->show();
}

void MainWindow::slotExit()
{
	QApplication::exit();
}

void MainWindow::slotLoginSuccess(const QByteArray xml)
{
	m_logined = true;
}

void MainWindow::slotAudioListLoaded(const QByteArray xml)
{
	m_pAudioModel->parseXml(xml);
}

void MainWindow::slotProfileLoaded(const QByteArray xml)
{
}

void MainWindow::slotLoginUnsuccess()
{
	m_logined = false;
}
