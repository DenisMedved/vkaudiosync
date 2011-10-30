#include "downloader.h"

using namespace Synch;

Downloader::Downloader(QObject *parent) :
	QThread(parent)
{
}

Downloader::~Downloader()
{
}

void Downloader::enqueue(VK::AudioModel *model)
{
	m_queue.enqueue(model);
}

VK::AudioModel* Downloader::dequeue()
{
	return m_queue.dequeue();
}

bool Downloader::ready()
{
	return m_dir->exists() && !m_queue.isEmpty();
}

void Downloader::run()
{
	m_needWait = false;
	QNetworkAccessManager *networkManager = new QNetworkAccessManager;
	QNetworkReply *reply;

	if (!ready())
		exit();

	qDebug() << "thread runing";

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
			qDebug() << "file created " << m_file->fileName();
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
				qDebug() << "success";
				m_file->write(reply->readAll());
				m_file->close();
				m_model->setStatus(VK::AudioModel::STATUS_SYNCHRONIZED);
			} else {
				qDebug() << "unsuccess : " << reply->errorString();
				m_file->remove();
			}
		}

		break;//TODO: remove after debug
	}
	delete m_file;
	delete networkManager;

	qDebug() << "thread finished";
	exec();
}

void Downloader::setDir(QDir *dir)
{
	m_dir = dir;
}

QDir* Downloader::dir()
{
	return m_dir;
}

void Downloader::downloadProgress( qint64 bytesReceived, qint64 bytesTotal)
{
	unsigned short percent = qRound(bytesReceived * 100 / bytesTotal);
	if (m_model->progress() != percent)
	{
		m_model->setProgress(percent);
		qDebug() << percent;
	}
}
