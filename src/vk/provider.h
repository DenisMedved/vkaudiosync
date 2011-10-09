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

#include <QString>
#include <QObject>
#include <QtWebKit>
#include <QtNetwork>
#include <QList>
#include <QSettings>
#include <QUrl>

#include "audiomodel.h"

namespace VK{

class Provider : public QObject
{
	Q_OBJECT

private:
	QString m_appId;
	QString m_uid;
	QString m_token;
	QString m_expire;
	QString m_lastError;
	QUrl m_authUrl;

	QSettings *m_settings;
	QWebView *m_webView;
	QNetworkAccessManager *m_networkManager;
	QList<AudioModel> *m_audioModels;

	void restoreCookieJar();
	void saveCookieJar();

private slots:
	void slotUrlChanged(const QUrl & url);
	void slotReplyFinished(QNetworkReply * reply );
	void slotLoadFinished(bool ok);

public:
	explicit Provider(QObject * parent = 0 );
	~Provider();
	void setApplicationId(QString appId);
	void getAccess() const;
	void getAudioList() const;
	void setSettings(QSettings *settings);
	QSettings* getSettings( ) const;

public slots:

signals:
	void modelsChanged(QList<AudioModel>*);
};
}
#endif // VKMODEL_H
