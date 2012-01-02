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

class AppSettings : QObject
{
Q_OBJECT

private:
	bool m_useConfig;
	QDir *m_pAppDir;
	QDir *m_pUserDir;
	QSettings *m_pSettings;
	QCoreApplication *m_pApp;
public:
	AppSettings(QObject *parent = 0);
	~AppSettings();

	void load();
};

#endif // MYSETTINGS_H
