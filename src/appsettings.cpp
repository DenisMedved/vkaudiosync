
#include "appsettings.h"

AppSettings::AppSettings(QObject *parent /*=0*/) : QObject(parent)
{
	m_useConfig = false;

	m_pUserDir = new QDir;
	m_pAppDir = new QDir;
	m_pSettings = new QSettings;
	m_pApp = QCoreApplication::instance();
	m_pCookieJar = new AppCookieJar(this);
	m_pCookieFile = new QFile(this);
	#ifdef Q_WS_X11
		m_pAppDir->setPath("/usr/share/vkaudiosync/");
		m_pUserDir->setPath(QDesktopServices::storageLocation(QDesktopServices::HomeLocation));

		if (!m_pUserDir->exists(".vkaudiosync")) {
			if ( m_pUserDir->mkdir(".vkaudiosync")) {
				m_pUserDir->cd(".vkaudiosync");
			}
		} else {
			m_pUserDir->cd(".vkaudiosync");
		}
	#else
		m_pAppDir->setPath(m_pApp->applicationDirPath());
		m_pUserDir->setPath(m_pApp->applicationDirPath());
	#endif

}

AppSettings::~AppSettings()
{
	save();

	delete m_pCookieFile;
	delete m_pSettings;
	delete m_pAppDir;
	delete m_pUserDir;
	delete m_pCookieJar;
}

void AppSettings::load()
{
#ifdef Q_WS_WIN
	m_useConfig = false;
#else
	QFile file;
	QString path;

	if (m_pUserDir->exists() && m_pUserDir->isReadable()) {
		path = m_pUserDir->absolutePath() + QDir::separator() + "settings.ini";
		file.setFileName(path);
		if (file.exists() && file.isWritable()) {
			m_pSettings->setPath(QSettings::IniFormat,QSettings::UserScope, path);
			m_useConfig = true;
		} else if (file.open(QIODevice::ReadWrite)) {
			file.close();
			m_pSettings->setPath(QSettings::IniFormat,QSettings::UserScope, path);
			m_useConfig = true;
		} else {
			m_useConfig = false;
			throw QString(tr("Permision denied: Can't write ") + path);
		}

		path = m_pUserDir->absolutePath() + QDir::separator() + "cookie.xml";
		file.setFileName(path);
		if (file.exists() && file.isWritable()) {
			setCookieFile(path);
		} else if (file.open(QIODevice::ReadWrite)) {
			file.close();
			setCookieFile(path);
		}
	} else {
		throw QString(tr("Permision denied: Can't read ") + m_pUserDir->path());
	}

	restore();
#endif
}

void AppSettings::setValue(const QString & key, const QVariant & value )
{
	if (m_useConfig) {
		m_pSettings->setValue(key, value);
	}
}

QVariant AppSettings::value ( const QString & key, const QVariant & defaultValue/* = QVariant() */) const
{
	if (m_useConfig) {
		return m_pSettings->value(key, defaultValue);
	} else {
		return QVariant();
	}
}

AppCookieJar* AppSettings::cookieJar() const
{
	return m_pCookieJar;
}

void AppSettings::clear()
{

}

void AppSettings::save()
{

}

void AppSettings::restore()
{

}

void AppSettings::setCookieFile(QString path)
{
	m_pCookieFile->setFileName(path);
	m_pCookieJar->setFile(m_pCookieFile);
}

QDir* AppSettings::applicationPath()
{
	return m_pAppDir;
}

QDir* AppSettings::userPath()
{
	return m_pUserDir;
}

QString AppSettings::translationPath()
{
	return m_pAppDir->path() + QDir::separator() + "translations";
}
