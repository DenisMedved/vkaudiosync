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

#ifndef VKMODEL_H
#define VKMODEL_H

#ifndef VK_APPLICATION_ID
#define VK_APPLICATION_ID 0 //mast defined by compiler
#endif

#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QTextCodec>

#include <QtWebKit>
#include <QtNetwork>

#include <QString>
#include <QObject>
#include <QList>
#include <QSettings>
#include <QUrl>

#include "profilefactory.h"
#include "audiofactory.h"
#include "audiomodel.h"
#include "profilemodel.h"

namespace VK {

class Provider : public QObject
{
	Q_OBJECT

private:
	QString *m_appId;
	QString *m_uid;
	QString *m_token;
	QString *m_expire;
	QString *m_lastError;
	QUrl *m_authUrl;
	QList<AudioModel> *m_audioModels;
	QWebView *m_webView;
	QNetworkAccessManager *m_networkManager;
	ProfileModel *m_profileModel;

	QSettings *m_settings;
	bool m_errorHandled;
	void restoreCookieJar();
	void saveCookieJar();
	void loadAudioList() ;
	void loadProfile() ;

private slots:
	void slotUrlChanged(const QUrl & url);
	void slotReplyFinished(QNetworkReply * reply );
	void slotLoadFinished(bool ok);

public:
	explicit Provider(QObject *parent = 0 );
	~Provider();
	void setApplicationId(QString appId);
	void login() ;
	void setSettings(QSettings *settings);
	bool isLogined() const;
	QSettings* getSettings( ) const;
	QList<VK:: AudioModel>* audioModels();

public slots:

signals:
	void modelsChanged(QList<VK::AudioModel>*);
	void loginSuccess(const VK::ProfileModel*);
	void loginUnsuccess();
};
}
#endif // VKMODEL_H
