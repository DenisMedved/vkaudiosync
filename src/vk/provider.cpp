#include <QObject>
#include <QString>
#include <QtNetwork>
#include <QDebug>
#include <QRegExp>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

#include "provider.h"

using namespace VK;

Provider::Provider (QObject *parent /*=0*/) : QObject(parent),
	m_webView(new QWebView),
	m_networkManager(new QNetworkAccessManager)
{
	connect(m_webView, SIGNAL(urlChanged(QUrl)),
		this,  SLOT(slotUrlChanged(QUrl)));
	connect(
		m_networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));
	connect(m_webView, SIGNAL(loadFinished(bool)),
		this, SLOT(slotLoadFinished(bool)));
}

Provider::~Provider()
{
	delete m_webView;
	delete m_networkManager;
}

void Provider::setApplicationId(QString appId)
{
	m_appId = appId;
}

void Provider::getAccess(){
/*
http://api.vkontakte.ru/blank.html
#access_token=387bff6e76ccacb0381a5de758386d2ed1b384c384c32bbef7e7273b5c2923b
&expires_in=86400
&user_id=3657181

http://api.vkontakte.ru/blank.html
#error=access_denied
&error_reason=user_denied
&error_description=User denied your request
*/
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
		//url.addQueryItem("access_token",m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}
/*
<response list="true">
 <audio>
  <aid>118272086</aid>
  <owner_id>3657181</owner_id>
  <artist>John Petrucci</artist>
  <title>Jaws of Life</title>
  <duration>449</duration>
  <url>http://cs4258.vkontakte.ru/u30445597/audio/3a40e57546f0.mp3</url>
 </audio>
 </response>
<error>
 <error_code>5</error_code>
 <error_msg>User authorization failed: no access_token passed.</error_msg>
 <request_params list="true">
  <param>
   <key>oauth</key>
   <value>1</value>
  </param>
  <param>
   <key>method</key>
   <value>audio.get.xml</value>
  </param>
 </request_params>
</error>
*/
void Provider::replyFinished(QNetworkReply * reply )
{
	qDebug() << reply->readAll();
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