#include "appcookiejar.h"

AppCookieJar::AppCookieJar(QObject *parent) :
	QNetworkCookieJar(parent)
{
	m_useFile = false;
	m_needSave = false;
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
	return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

void AppCookieJar::clear()
{

}

void AppCookieJar::save()
{
	/*if (m_useFile && m_pFile->open(QIODevice::WriteOnly)) {
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
	}*/
}

void AppCookieJar::restore()
{
	/*if (m_useFile && m_pFile->open(QIODevice::ReadOnly)) {
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
	}*/
}

