#ifndef APPCOOKIEJAR_H
#define APPCOOKIEJAR_H

#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QList>
#include <QUrl>
#include <QtXml>

class AppCookieJar : public QNetworkCookieJar
{
	Q_OBJECT

protected:
	QFile *m_pFile;
	QList<QNetworkCookie> m_cookieList;

	bool m_useFile;
	bool m_needSave;

public:
	explicit AppCookieJar(QObject *parent = 0);
	virtual ~AppCookieJar();

	void setFile(QFile *pFile);
	QFile* file() const;

	virtual QList<QNetworkCookie>	cookiesForUrl ( const QUrl & url ) const;
	virtual bool setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url );

	void clear();
	void save();
	void restore();

signals:

public slots:

};

#endif // APPCOOKIEJAR_H
