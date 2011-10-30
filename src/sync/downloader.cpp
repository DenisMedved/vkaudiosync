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

	/*connect(networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(finished(QNetworkReply*)));*/

	//connect(reply, SIGNAL(finished()), this, SLOT())

	if (!ready())
		exit();
	qDebug() << "thread runing";


	VK::AudioModel *model;

	m_file = new QFile;
	while (!m_queue.isEmpty())
	{
		model = dequeue();
		m_name = QString("%1 - %2.mp3")
				.arg(model->artist())
				.arg(model->title());

		m_file->setFileName(m_dir->path() + QDir::separator() + m_name);
		if (m_file->open(QIODevice::WriteOnly))
		{
			qDebug() << "file created " << m_file->fileName();
			QNetworkRequest request;
			request.setUrl(model->url());
			reply = networkManager->get(request);

			QEventLoop loop;
			connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
			loop.exec();

			if (reply->error() == QNetworkReply::NoError) {
				qDebug() << "success";
				m_file->write(reply->readAll());
				m_file->close();
				model->setStatus(VK::AudioModel::STATUS_SYNCHRONIZED);
			} else {
				qDebug() << "unsuccess : " << reply->errorString();
				m_file->remove();
			}
		}

		break;
	}
	delete m_file;


	delete networkManager;

	qDebug() << "thread finished";
	exec();
}

void Downloader::finished(QNetworkReply* reply)
{
	m_file->write(reply->readAll());
	m_needWait = false;
	qDebug() << "unlock";
}

void Downloader::setDir(QDir *dir)
{
	m_dir = dir;
}

QDir* Downloader::dir()
{
	return m_dir;
}
