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

#include "vkservice.h"

namespace VK {

VKService::VKService (QWidget *parent /*=0*/) : QObject(parent)
{
	m_webView = new QWebView;
	m_networkManager = new QNetworkAccessManager(this);

	m_webView->resize(640,420);
	int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	m_webView->move((width - m_webView->width()) / 2 , (height - m_webView->height()) / 3);

	m_authUrl.setUrl("http://api.vkontakte.ru/oauth/authorize");
	m_authUrl.addQueryItem("client_id", QString::number(VK_APPLICATION_ID).toAscii());
	m_authUrl.addQueryItem("scope","audio");
	m_authUrl.addQueryItem("redirect_uri","http://api.vkontakte.ru/blank.html");
	m_authUrl.addQueryItem("display","popup");
	m_authUrl.addQueryItem("response_type","token");

	m_errorHandled = false;

	connect(m_webView, SIGNAL(urlChanged(QUrl)),
		this, SLOT(slotUrlChanged(QUrl)));
	connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slotReplyFinished(QNetworkReply*)));
	connect(m_webView, SIGNAL(loadFinished(bool)),
		this, SLOT(slotLoadFinished(bool)));
}

VKService::~VKService()
{
	delete m_webView;
	delete m_networkManager;
}

void VKService::setApplicationId(QString appId)
{
	m_appId = appId;
}

void VKService::login()
{
	m_webView->load(m_authUrl);
	emit opened();
}

void VKService::loadAudioList()
{
	if (m_lastError.isEmpty() && !m_token.isEmpty() && !m_expire.isEmpty()) {
		QUrl url("https://api.vkontakte.ru/method/audio.get.xml");
		url.addQueryItem("access_token",m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}

void VKService::loadProfile()
{
	if (m_lastError.isEmpty() && !m_token.isEmpty() && !m_expire.isEmpty() && !m_uid.isEmpty()) {
		QUrl url("https://api.vkontakte.ru/method/getProfiles.xml");
		url.addQueryItem("uids",m_uid);
		url.addQueryItem("fields","uid, first_name, last_name, photo, photo_medium");
		url.addQueryItem("access_token",m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}

void VKService::slotReplyFinished(QNetworkReply *reply)
{
	const QByteArray response = reply->readAll();

	if ("/method/audio.get.xml" == reply->url().path()) {
		emit audioListLoaded(response);
	} else if ("/method/getProfiles.xml" == reply->url().path()) {
		if (isLogined()) {
			emit loginSuccess(response);
			emit profileLoaded(response);
		}
	}
}

void VKService::slotUrlChanged(const QUrl &url )
{
	QString urlAsString = url.toString();
	if (urlAsString.isEmpty() || url.path() == "/oauth/authorize")
		return;

	urlAsString.replace('#','?');
	QUrl chnagedUrl(urlAsString);
	m_lastError = chnagedUrl.queryItemValue("error");
	if (m_lastError.isEmpty()) {
		m_token = chnagedUrl.queryItemValue("access_token");
		m_expire = chnagedUrl.queryItemValue("expires_in");
		m_uid = chnagedUrl.queryItemValue("user_id");
		loadProfile();
		loadAudioList();
	} else {
		m_token.clear();
		m_expire.clear();
		emit loginUnsuccess();
		m_errorHandled = true;
	}
	m_webView->close();
	emit closed();
}

void VKService::slotLoadFinished(bool ok)
{
	if (!ok && ! m_errorHandled) {
		m_webView->close();
		m_lastError.append("connection failure");
		QMessageBox::critical(m_webView,"Connection error",tr("Connect to vk com failed"));
		emit loginUnsuccess();
	} else if (m_webView->url().path() == m_authUrl.path()) {
		m_webView->show();
	} else {
		m_webView->close();
	}

	emit closed(); //TODO: not realy closed
}

bool VKService::isLogined() const
{
	return !m_expire.isEmpty() && m_lastError.isEmpty();
}

void VKService::logout()
{
	//TODO: clear cookies
}

void VKService::setCookieJar(QNetworkCookieJar *cookieJar)
{
	m_pCookieJar = cookieJar;
	m_webView->page()->networkAccessManager()->setCookieJar(m_pCookieJar);
}

}
