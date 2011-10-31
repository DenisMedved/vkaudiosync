#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QThread>
#include <QQueue>
#include <QUrl>
#include <QDir>
#include <QtNetwork>
#include <QFile>
#include <QDebug>
#include <QEventLoop>

#include "../vk/audiomodel.h"

namespace VK {
class Downloader;
}

namespace Synch {
class Downloader : public QThread
{
	Q_OBJECT

protected:
	QDir *m_dir;
	QQueue<VK::AudioModel*> m_queue;
	QString m_name;
	QFile* m_file;
	VK::AudioModel *m_model;

	bool ready();
	bool m_needWait;
	void run();
public:
	explicit Downloader(QObject *parent = 0);
	~Downloader();
	void setDir(QDir *dir);
	QDir* dir();
	void enqueue(VK::AudioModel *model);
	VK::AudioModel * dequeue();

signals:
	void modelChanged();

protected slots:
	void downloadProgress( qint64 bytesReceived, qint64 bytesTotal);
};
}
#endif // DOWNLOADER_H
