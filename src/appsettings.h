#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QCoreApplication>
#include <QObject>
#include <QDir>
#include <QSettings>

//use in impl.
#include <QDesktopServices>
#include <QFile>
#include <QtXml>
#include <QVariant>

#include "appcookiejar.h"

class AppSettings : QObject
{
Q_OBJECT

private:
	bool m_useConfig;
	QDir *m_pAppDir;
	QDir *m_pUserDir;
	QSettings *m_pSettings;
	QCoreApplication *m_pApp;
	AppCookieJar *m_pCookieJar;

public:
	AppSettings(QObject *parent = 0);
	~AppSettings();

	void load();
	void setValue(const QString & key, const QVariant & value );
	QVariant value ( const QString & key, const QVariant & defaultValue = QVariant() ) const;

	AppCookieJar* cookieJar() const;
	void clear();
};

#endif // MYSETTINGS_H
