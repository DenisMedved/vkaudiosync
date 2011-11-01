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

#include "provider.h"

using namespace VK;

Provider::Provider (QObject *parent /*=0*/) : QObject(parent)
{
	m_appId = new QString;
	m_uid = new QString;
	m_token = new QString;
	m_expire = new QString;
	m_lastError = new QString;
	m_authUrl = new QUrl;
	m_audioModels = new QList<AudioModel>;
	m_webView = new QWebView;
	m_networkManager = new QNetworkAccessManager(this);
	m_profileModel = new ProfileModel;
	m_settings = new QSettings(this);

	m_webView->resize(640,420);
	int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	m_webView->move((width - m_webView->width()) / 2 , (height - m_webView->height()) / 3);

	m_authUrl->setUrl("http://api.vkontakte.ru/oauth/authorize");
	m_authUrl->addQueryItem("client_id","2169954");
	m_authUrl->addQueryItem("scope","audio");
	m_authUrl->addQueryItem("redirect_uri","http://api.vkontakte.ru/blank.html");
	m_authUrl->addQueryItem("display","popup");
	m_authUrl->addQueryItem("response_type","token");

	m_errorHandled = false;
	connect(m_webView, SIGNAL(urlChanged(QUrl)),
		this, SLOT(slotUrlChanged(QUrl)));
	connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slotReplyFinished(QNetworkReply*)));
	connect(m_webView, SIGNAL(loadFinished(bool)),
		this, SLOT(slotLoadFinished(bool)));
}

Provider::~Provider()
{
	saveCookieJar();

	delete m_appId;
	delete m_uid;
	delete m_token;
	delete m_expire;
	delete m_lastError;
	delete m_authUrl;
	delete m_audioModels;
	delete m_webView;
	delete m_networkManager;
	delete m_profileModel;
}

void Provider::restoreCookieJar()
{
	if (!m_settings)
		return;

	m_settings->beginGroup("cookies");
	QList<QNetworkCookie> cookieList;
	QStringList keys = m_settings->childKeys();
	for (int index=0; index < keys.count(); ++index)
	{
		QNetworkCookie cookie(m_settings->value(keys.at(index)).toByteArray().replace("**",";"));
		cookieList.append(cookie);
		m_settings->remove(keys.at(index));
	}
	m_webView->page()->networkAccessManager()->cookieJar()->setCookiesFromUrl(cookieList, *m_authUrl);
	m_settings->endGroup();
}

void Provider::saveCookieJar()
{
	if (!m_settings)
		return ;

	QList<QNetworkCookie> cookies = m_webView->page()->networkAccessManager()->cookieJar()->cookiesForUrl(*m_authUrl);
	m_settings->beginGroup("cookies");
	for (int index = 0; index < cookies.count() ; ++index )
	{
		m_settings->setValue(QString::number(index),QString( cookies.at(index).toRawForm().replace(";","**")));//TODO: bad bad hack for escape ';'
	}
	m_settings->endGroup();
}

void Provider::setApplicationId(QString appId)
{
	(*m_appId) = appId;
}

void Provider::login()
{
	m_webView->load(*m_authUrl);
	m_webView->show();
}

void Provider::slotUrlChanged(const QUrl &url )
{

	QString urlAsString = url.toString();
	if (urlAsString.isEmpty() || url.path() == "/oauth/authorize")
		return;

	urlAsString.replace('#','?');
	QUrl chnagedUrl(urlAsString);
	(*m_lastError) = chnagedUrl.queryItemValue("error");
	if (m_lastError->isEmpty())
	{
		(*m_token) = chnagedUrl.queryItemValue("access_token");
		(*m_expire) =  chnagedUrl.queryItemValue("expires_in");
		loadAudioList();
		loadProfile();
	} else {
		m_token->clear();
		m_expire->clear();
		emit loginUnsuccess();
		m_errorHandled = true;
	}
	m_webView->hide();
}

void Provider::loadAudioList()
{
	if (m_lastError->isEmpty() && !m_token->isEmpty() && !m_expire->isEmpty())
	{
		QUrl url("https://api.vkontakte.ru/method/audio.get.xml");
		url.addQueryItem("access_token",*m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}

void Provider::loadProfile()
{
	if (m_lastError->isEmpty() && !m_token->isEmpty() && !m_expire->isEmpty())
	{
		QUrl url("https://api.vkontakte.ru/method/getVariable.xml");
		url.addQueryItem("key","1281");
		url.addQueryItem("access_token",*m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}

void Provider::slotReplyFinished(QNetworkReply * reply )
{
	QByteArray xml (reply->readAll());
	if ("/method/audio.get.xml" == reply->url().path())
	{
		m_audioModels->clear();
		AudioFactory::parseAudioModel(&xml, m_audioModels);
		if (m_audioModels->length())
		{
			emit modelsChanged(*m_audioModels);
		}
	} else if ("/method/getVariable.xml" == reply->url().path()) {
		ProfileFactory::parseProfileModel(&xml, m_profileModel);
		if (isLogined())
		{
			saveCookieJar();
			emit loginSuccess(*m_profileModel);
		}
	}
}

void Provider::slotLoadFinished(bool ok)
{
	if (!ok && ! m_errorHandled)
	{
		m_webView->close();
		(*m_lastError) = "connection failure";
		QMessageBox::critical(m_webView,"Connection error","Connect to vk com failed");
		emit loginUnsuccess();
	}
}

QSettings* Provider::getSettings() const
{
	return m_settings;
}

void Provider::setSettings(QSettings *settings)
{
	m_settings = settings;
	restoreCookieJar();
}

bool Provider::isLogined() const
{
	if (!m_expire->isEmpty() && m_lastError->isEmpty() && !m_profileModel->name().isEmpty())
	{
		return true;
	}
	return false;
}

QList<VK:: AudioModel>* Provider::audioModels()
{
	return m_audioModels;
}
