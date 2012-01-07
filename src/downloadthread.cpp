#include "downloadthread.h"


DownloadThread::DownloadThread(QObject *parent) :
	QThread(parent)
{
}

DownloadThread::~DownloadThread()
{
}

void DownloadThread::setAudioListModel(AudioListModel *model)
{
	m_pAudioListModel = model;
}

void DownloadThread::run()
{
/*	m_needWait = false;
	QNetworkAccessManager *networkManager = new QNetworkAccessManager;
	QNetworkReply *reply;

	if (!ready())
		exit();

	m_file = new QFile;
	while (!m_queue.isEmpty())
	{
		m_model = dequeue();
		m_name = QString("%1 - %2.mp3")
				.arg(m_model->artist())
				.arg(m_model->title());

		m_file->setFileName(m_dir->path() + QDir::separator() + m_name);
		if (m_file->open(QIODevice::WriteOnly))
		{
			QNetworkRequest request;
			request.setUrl(m_model->url());
			reply = networkManager->get(request);

			QEventLoop loop;
			connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
					this,SLOT(downloadProgress(qint64,qint64)));
			connect(reply, SIGNAL(finished()),
					&loop, SLOT(quit()));

			loop.exec();

			if (reply->error() == QNetworkReply::NoError) {
				m_file->write(reply->readAll());
				m_file->close();
				m_model->setStatus(VK::AudioModel::STATUS_SYNCHRONIZED);
			} else {
				m_file->remove();
			}
		}

	}
	delete m_file;
	delete n*=etworkManager;
*/
	exec();
}

void DownloadThread::setDir(QDir *dir)
{
	m_dir = dir;
}

void DownloadThread::downloadProgress( qint64 bytesReceived, qint64 bytesTotal)
{
	/*unsigned short percent = qRound(bytesReceived * 100 / bytesTotal);
	if (m_model->progress() != percent)
	{
		m_model->setProgress(percent);
		emit modelChanged();
	}*/
}

void DownloadThread::enqueue(QModelIndex &index)
{
	m_queue.enqueue(index);
}

QModelIndex DownloadThread::dequeue()
{
	return m_queue.dequeue();
}
