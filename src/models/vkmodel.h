#ifndef VKMODEL_H
#define VKMODEL_H

#include <QString>
#include <QObject>
#include <QtWebKit>
#include <QtNetwork>

class VkModel : public QObject
{
	Q_OBJECT

protected:
	QString m_appId;
	QString m_uid;
	QString m_token;
	QString m_expire;
	QString m_lastError;

	QWebView *m_webView;
	QNetworkAccessManager * m_networkManager;
public:
	explicit VkModel(QObject * parent = 0 );
	~VkModel();
	void setApplicationId(QString appId);
	void  getAccess();
	void getAudioList();

signals:

protected slots:
	void slotUrlChanged(const QUrl & url);
	void replyFinished(QNetworkReply * reply );
public slots:

};

#endif // VKMODEL_H
