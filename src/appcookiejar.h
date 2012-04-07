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

};

#endif // APPCOOKIEJAR_H
