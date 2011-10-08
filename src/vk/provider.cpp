#include <QtNetwork>

#include <QObject>
#include <QString>
#include <QDebug>
#include <QRegExp>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QByteArray>
#include <QList>

#include "audiomodel.h"
#include "audiofactory.h"
#include "provider.h"

using namespace VK;

Provider::Provider (QObject *parent /*=0*/) : QObject(parent),
	m_webView(new QWebView),
	m_networkManager(new QNetworkAccessManager),
	m_audioModels(new QList<AudioModel>)
{
	connect(m_webView, SIGNAL(urlChanged(QUrl)),
		this, SLOT(slotUrlChanged(QUrl)));
	connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slotReplyFinished(QNetworkReply*)));
	connect(m_webView, SIGNAL(loadFinished(bool)),
		this, SLOT(slotLoadFinished(bool)));
}

Provider::~Provider()
{
	delete m_audioModels;
	delete m_webView;
	delete m_networkManager;
}

void Provider::setApplicationId(QString appId)
{
	m_appId = appId;
}

void Provider::getAccess()
{
	QUrl authUrl("http://api.vkontakte.ru/oauth/authorize");
	authUrl.addQueryItem("client_id","2169954");
	authUrl.addQueryItem("scope","audio");
	authUrl.addQueryItem("redirect_uri","http://api.vkontakte.ru/blank.html");
	authUrl.addQueryItem("display","popup");
	authUrl.addQueryItem("response_type","token");
	m_webView->resize(640,420);
	int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	m_webView->move((width - m_webView->width()) / 2 , (height - m_webView->height()) / 3);
	m_webView->load(authUrl);
	m_webView->show();
}

void Provider::slotUrlChanged(const QUrl & url )
{
	QString urlAsString = url.toString();

	if (urlAsString.isEmpty() || url.path() == "/oauth/authorize")
		return;

	urlAsString.replace('#','?');
	QUrl chnagedUrl(urlAsString);
	m_lastError = chnagedUrl.queryItemValue("error");
	if (m_lastError.isEmpty())
	{
		m_token = chnagedUrl.queryItemValue("access_token");
		m_expire =  chnagedUrl.queryItemValue("expires_in");
	} else {
		m_token.clear();
		m_expire.clear();
	}
	m_webView->hide();
}

void Provider::getAudioList()
{
	if (m_lastError.isEmpty() && !m_token.isEmpty() && !m_expire.isEmpty())
	{
		QUrl url("https://api.vkontakte.ru/method/audio.get.xml");
		url.addQueryItem("access_token",m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}

void Provider::slotReplyFinished(QNetworkReply * reply )
{
	if ("/method/audio.get.xml" == reply->url().path())
	{
		QByteArray xml (reply->readAll());
		m_audioModels->clear();
		AudioFactory::parseAudioModel(&xml, m_audioModels);

		if (m_audioModels->length())
		{
			emit modelsChanged(m_audioModels);
		} else {
			//unsuccess
		}
	}
}

void Provider::slotLoadFinished(bool ok)
{
	if (!ok)
	{
		m_lastError = "connection failure";
		m_webView->hide();
		QMessageBox::critical(m_webView,"Connection error","Connect to vk com failed");
	}
}
