#ifndef VKMODEL_H
#define VKMODEL_H

#include <QString>
#include <QObject>
#include <QtWebKit>
#include <QtNetwork>
#include <QList>
#include <QSettings>
#include <QUrl>

#include "audiomodel.h"

namespace VK{

class Provider : public QObject
{
	Q_OBJECT

private:
	QString m_appId;
	QString m_uid;
	QString m_token;
	QString m_expire;
	QString m_lastError;
	QUrl m_authUrl;

	QSettings *m_settings;
	QWebView *m_webView;
	QNetworkAccessManager *m_networkManager;
	QList<AudioModel> *m_audioModels;

	void restoreCookieJar();
	void saveCookieJar();

private slots:
	void slotUrlChanged(const QUrl & url);
	void slotReplyFinished(QNetworkReply * reply );
	void slotLoadFinished(bool ok);

public:
	explicit Provider(QObject * parent = 0 );
	~Provider();
	void setApplicationId(QString appId);
	void getAccess() const;
	void getAudioList() const;
	void setSettings(QSettings *settings);
	QSettings* getSettings( ) const;


public slots:

signals:
	void modelsChanged(QList<AudioModel>*);
};
}
#endif // VKMODEL_H
