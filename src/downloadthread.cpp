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
	if (m_queue.isEmpty())
		quit();

	m_needQuit = false;

	QNetworkAccessManager *networkManager = new QNetworkAccessManager;
	QNetworkReply *reply;

	m_file = new QFile;
	QString tmpName;
	while (!m_queue.isEmpty()) {

		if (m_needQuit)
			exit();


		m_target = dequeue();
		m_name = QString("%1 - %2.mp3")
				.arg(m_pAudioListModel->data(m_target, AudioListModel::ROLE_ARTIST).toString())
				.arg(m_pAudioListModel->data(m_target, AudioListModel::ROLE_TITLE).toString());

		tmpName = QString("%1.%2")
				.arg(m_name)
				.arg("tmp");

		m_file->setFileName(m_dir->path() + QDir::separator() + tmpName);

		if (m_file->open(QIODevice::WriteOnly)) {
			QNetworkRequest request;
			request.setUrl(m_pAudioListModel->data(m_target, AudioListModel::ROLE_URL).toUrl());
			reply = networkManager->get(request);

			QEventLoop loop;
			connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
					this,SLOT(downloadProgress(qint64,qint64)));
			connect(reply, SIGNAL(finished()),
					&loop, SLOT(quit()));

			loop.exec();

			if (reply->error() == QNetworkReply::NoError && !m_needQuit) {
				m_file->write(reply->readAll());
				if (!m_file->rename(QString(m_dir->path() + QDir::separator() + m_name)))
					qDebug() << "rename error ";
				m_file->close();
				m_pAudioListModel->setData(m_target,QVariant(AudioItem::STATUS_SYNCHRONIZED),AudioListModel::ROLE_STATUS);
			} else {
				m_file->remove();
			}
		}
	}
	delete m_file;
	delete networkManager;

	exec();
	quit();
}

void DownloadThread::setDir(QDir *dir)
{
	m_dir = dir;
}

void DownloadThread::downloadProgress( qint64 bytesReceived, qint64 bytesTotal)
{
	if (m_needQuit)
		exit();


	unsigned short percent = qCeil(bytesReceived * 100 / bytesTotal);
	unsigned short progress = m_pAudioListModel->data(m_target, AudioListModel::ROLE_PROGRESS).toInt();
	if (progress != percent) {
		m_pAudioListModel->setData(m_target, QVariant(percent), AudioListModel::ROLE_PROGRESS);
	}
}

void DownloadThread::enqueue(const QModelIndex &index)
{
	m_queue.enqueue(index);
}

QModelIndex DownloadThread::dequeue()
{
	return m_queue.dequeue();
}

const QQueue<QModelIndex>* DownloadThread::queue() const
{
	return &m_queue;
}

void DownloadThread::slotFinished()
{
	m_pAudioListModel->setData(m_target, QVariant(100), AudioListModel::ROLE_PROGRESS);
	m_pAudioListModel->setData(m_target, QVariant(AudioItem::STATUS_SYNCHRONIZED), AudioListModel::ROLE_STATUS);
	quit();
}

void DownloadThread::stopSync()
{
	m_needQuit = true;
	if (m_queue.isEmpty())
		quit();
}
