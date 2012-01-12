#include "appcookiejar.h"

AppCookieJar::AppCookieJar(QObject *parent) :
	QNetworkCookieJar(parent)
{
	m_useFile = false;
	m_needSave = false;

	m_authUrl.setUrl("http://api.vkontakte.ru/oauth/authorize");
	m_authUrl.addQueryItem("client_id", QString::number(VK_APPLICATION_ID).toAscii());
	m_authUrl.addQueryItem("scope","audio");
	m_authUrl.addQueryItem("redirect_uri","http://api.vkontakte.ru/blank.html");
	m_authUrl.addQueryItem("display","popup");
	m_authUrl.addQueryItem("response_type","token");
}

AppCookieJar::~AppCookieJar()
{
}

void AppCookieJar::setFile(QFile *pFile)
{
	m_useFile = true;
	m_pFile = pFile;
}

QFile* AppCookieJar::file() const
{
	return m_pFile;
}

QList<QNetworkCookie> AppCookieJar::cookiesForUrl ( const QUrl & url ) const
{
	return QNetworkCookieJar::cookiesForUrl(url);
}

bool AppCookieJar::setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url )
{
	m_cookieList = cookieList;
	bool result = QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
	save();
	return result;
}

void AppCookieJar::clear()
{

}

void AppCookieJar::save()
{
	if (m_useFile && m_pFile->open(QIODevice::WriteOnly)) {
		QTextStream stream(m_pFile);
		QDomDocument dom;
		dom.setContent(m_pFile);
		QDomElement root;
		root.setTagName("cookies");
		for (int index = 0; index < m_cookieList.size() ; ++index ) {
			QDomElement cookie;
			cookie.setTagName("cookie");
			cookie.setNodeValue(QString(m_cookieList.at(index).toRawForm()));
			root.appendChild(cookie);
		}
		dom.appendChild(root);
		dom.save(stream,0);
		m_pFile->close();
	}
}

void AppCookieJar::restore()
{
	if (m_useFile && m_pFile->open(QIODevice::ReadOnly)) {
		QList<QNetworkCookie> list;
		QDomDocument dom;
		dom.setContent(m_pFile);
		QDomElement root = dom.firstChild().toElement();
		QDomElement cookie = root.firstChildElement();
		if (root.tagName() == "cookies") {
			while (!cookie.isNull()) {
				QNetworkCookie c (cookie.nodeValue().toUtf8());
				list.append(c);
				cookie.nextSibling();
			}
		}
		m_pFile->close();
		setCookiesFromUrl(list,m_authUrl);
	}
}

