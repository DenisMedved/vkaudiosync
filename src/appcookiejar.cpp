#include "appcookiejar.h"

AppCookieJar::AppCookieJar(QObject *parent) :
	QNetworkCookieJar(parent)
{
	m_useFile = false;
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
	QNetworkCookieJar::cookiesForUrl(url);
}

bool AppCookieJar::setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url )
{
	return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

void AppCookieJar::clear()
{
	m_cookieList.clear();
	save();
}
void AppCookieJar::save()
{

}

void AppCookieJar::restore()
{

}
