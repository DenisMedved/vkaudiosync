/*
  *  VKAudioSync
  *  Copyright (C) 2011 Denis Medved <thebucefal@gmail.com>
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "thread.h"

using namespace Synch;

Thread::Thread(QObject * parent) : QThread(parent)
{
	/*connect(&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinished(QNetworkReply* reply)));*/
}

void Thread::run()
{
	//QThread::run();
	qDebug() << "thread runing";
	m_networkAccessManager = new QNetworkAccessManager;
	QNetworkRequest request;
	QNetworkReply *reply;
	QString filename;
	VK::AudioModel *model;
	while (!m_queue.isEmpty())
	{
		model = m_queue.dequeue();
		filename.clear();
		filename.append(model->artist());
		filename.append(" - ");
		filename.append(model->title());
		filename.append(".mp3");

		m_file = new QFile();
		m_file->setFileName(m_dir->path() + QDir::separator() + filename);
		if (m_file->open(QIODevice::WriteOnly) )
		{
			request.setUrl(model->url());
			reply = m_networkAccessManager->get(request);
			m_file->write(reply->readAll());
			model->setStatus(VK::AudioModel::STATUS_SYNCHRONIZED);
			m_file->close();

			qDebug() << m_file->fileName();
			sleep(3);
		}

		delete m_file;
		delete m_networkAccessManager;

		qDebug() << "thread closed";
		exec();
	}

	exec();
}

void Thread::enqueue(VK::AudioModel *model)
{
	m_queue.enqueue(model);
}

void Thread::setDir(QDir *dir)
{
	m_dir = dir;
}

void Thread::replyFinished(QNetworkReply* reply)
{
	m_file->write(reply->readAll());
}
