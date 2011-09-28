#include <QObject>
#include <QString>
#include <QtNetwork>
#include <QDebug>
#include <QRegExp>
#include <QApplication>
#include <QDesktopWidget>
#include "vkmodel.h"

VkModel::VkModel (QObject *parent /*=0*/) : QObject(parent),
	m_webView(new QWebView),
	m_networkManager(new QNetworkAccessManager)
{
	connect(m_webView, SIGNAL(urlChanged(QUrl)), this,  SLOT(slotUrlChanged(QUrl)));
	connect(
		m_networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));
}

VkModel::~VkModel()
{
	delete m_webView;
}

void VkModel::setApplicationId(QString appId){
	m_appId = appId;
}

void VkModel::getAccess(){
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
	m_webView->move((width - m_webView->width()) / 2 , (height - m_webView->height()) / 2);
	m_webView->load(authUrl);
	m_webView->show();
}
void VkModel::slotUrlChanged(const QUrl & url )
{
	QString changedUrlStr(url.toString());
	changedUrlStr.replace('#','?');
	QUrl chnagedUrl(changedUrlStr);
	m_lastError = chnagedUrl.queryItemValue("error");
	if (m_lastError.isEmpty())
	{
		m_token = chnagedUrl.queryItemValue("access_token");
		m_expire =  chnagedUrl.queryItemValue("expires_in");
	} else {
		m_token.clear();
		m_expire.clear();
	}

	//m_webView->hide();
}

void VkModel::getAudioList()
{
	if (m_lastError.isEmpty() && !m_token.isEmpty() && !m_expire.isEmpty())
	{
		QUrl url("https://api.vkontakte.ru/method/audio.get.xml");
		url.addQueryItem("access_token",m_token);
		QNetworkRequest request(url);
		m_networkManager->get(request);
	}
}
void VkModel::replyFinished(QNetworkReply * reply )
{
	qDebug() << reply->readAll();
}
