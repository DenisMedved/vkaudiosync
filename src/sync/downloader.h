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
