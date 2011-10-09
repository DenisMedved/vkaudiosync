#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

#include "audiofactory.h"
#include "provider.h"

using namespace VK;

Provider::Provider (QObject *parent /*=0*/) : QObject(parent)
{
	m_webView = new QWebView;
	m_webView->resize(640,420);
	int width = QApplication::desktop()->width();
	int height = QApplication::desktop()->height();
	m_webView->move((width - m_webView->width()) / 2 , (height - m_webView->height()) / 3);

	m_networkManager = new QNetworkAccessManager(this);
	m_audioModels = new QList<AudioModel>;

	m_authUrl.setUrl("http://api.vkontakte.ru/oauth/authorize");
	m_authUrl.addQueryItem("client_id","2169954");
	m_authUrl.addQueryItem("scope","audio");
	m_authUrl.addQueryItem("redirect_uri","http://api.vkontakte.ru/blank.html");
	m_authUrl.addQueryItem("display","popup");
	m_authUrl.addQueryItem("response_type","token");

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
	delete m_audioModels;
	delete m_webView;
	delete m_networkManager;
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
	}
	m_webView->page()->networkAccessManager()->cookieJar()->setCookiesFromUrl(cookieList, m_authUrl);
	m_settings->endGroup();
}

void Provider::saveCookieJar()
{
	if (!m_settings)
		return ;

	QList<QNetworkCookie> cookies = m_webView ->page()
										      ->networkAccessManager()
										      ->cookieJar()
										      ->cookiesForUrl(m_authUrl);
	m_settings->beginGroup("cookies");
	for (int index = 0; index < cookies.count() ; ++index )
	{
		m_settings->setValue(QString::number(index),QString( cookies.at(index).toRawForm().replace(";","**")));//TODO: bad bad hack for escape ';'
	}
	m_settings->endGroup();
}

void Provider::setApplicationId(QString appId)
{
	m_appId = appId;
}

void Provider::getAccess() const
{
	m_webView->load(m_authUrl);
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

void Provider::getAudioList() const
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
		QApplication::exit();
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


