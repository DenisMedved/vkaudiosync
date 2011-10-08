#ifndef VKMODEL_H
#define VKMODEL_H

#include <QString>
#include <QObject>
#include <QtWebKit>
#include <QtNetwork>
#include <QList>

#include "audiomodel.h"

namespace VK{

class Provider : public QObject
{
	Q_OBJECT

protected:
	QString m_appId;
	QString m_uid;
	QString m_token;
	QString m_expire;
	QString m_lastError;

	QWebView *m_webView;
	QNetworkAccessManager *m_networkManager;
	QList<AudioModel> *m_audioModels;

public:
	explicit Provider(QObject * parent = 0 );
	~Provider();
	void setApplicationId(QString appId);
	void getAccess();
	void getAudioList();

signals:
	void modelsChanged(QList<AudioModel>*);

protected slots:
	void slotUrlChanged(const QUrl & url);
	void slotReplyFinished(QNetworkReply * reply );
	void slotLoadFinished(bool ok);

public slots:

};
}
#endif // VKMODEL_H
