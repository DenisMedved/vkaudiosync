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

#include "synchronizer.h"

using namespace Synch;

Synchronizer::Synchronizer(QObject *parent) :
	QObject(parent)
{
	m_threadCount = 5;
	m_downloader = new Downloader[m_threadCount];

	connect(m_downloader, SIGNAL(modelChanged()),
			this,  SLOT(slotThreadChangeModel()));
}

Synchronizer::~Synchronizer()
{
	delete[] m_downloader;
}

void Synchronizer::setDir(QDir dir)
{
	m_settings->setValue("dir",dir.path());
	m_dir = dir;
}

QDir Synchronizer::dir() const
{
	return m_dir;
}

void Synchronizer::setSettings(QSettings *settings)
{
	m_settings = settings;
	if (!m_settings->value("dir").toString().isEmpty())
	{
		m_dir = QDir(m_settings->value("dir").toString());
	}
}

QSettings* Synchronizer::settings() const
{
	return m_settings;
}

void Synchronizer::setAudioList(QList<VK::AudioModel>* list)
{
	m_audioList = list;
}

void Synchronizer::synchronize()
{
	bool changed = false;

	if (m_dir.path().isEmpty() || !m_dir.isReadable())
		return;

	m_dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );
	QFileInfoList files = m_dir.entryInfoList();
	QList<VK::AudioModel>::iterator model;
	bool modelFinded ;
	for (int i = 0; i < files.size(); ++i)
	{
		modelFinded = false;
		QFileInfo fileInfo = files.at(i);
		for (model = m_audioList->begin(); model != m_audioList->end(); ++model)
		{
			if (VK::AudioModel::STATUS_UNDEFINED == model->status())
			{
				QString fullName = model->artist();
				fullName.append(" - ");
				fullName.append(model->title());
				if (fileInfo.exists() &&  fullName == fileInfo.baseName() && "mp3" == fileInfo.suffix())
				{
					modelFinded = true;
					model->setStatus(VK::AudioModel::STATUS_SYNCHRONIZED);
					if (!changed)
						changed = true;
				}
			}
		}
		if (modelFinded)
		{
			//TODO: upload file  to vk
		}
	}
	unsigned short threadIndex = 0, threadCounter = 0;

	for (unsigned short i=0; i < m_threadCount; ++i)
	{
		m_downloader[i].clearQueue();
	}


	for (model = m_audioList->begin(); model != m_audioList->end(); ++model)
	{
		if (VK::AudioModel::STATUS_UNDEFINED == model->status()
				|| VK::AudioModel::STATUS_NEEDDOWNLOAD == model->status())
		{
			model->setStatus(VK::AudioModel::STATUS_NEEDDOWNLOAD);

			threadIndex = threadCounter % m_threadCount;
			m_downloader[threadIndex].enqueue(&(*model));
			++threadCounter;

			if (!changed)
				changed = true;
		}
	}

	for (unsigned short i=0; i < m_threadCount; ++i)
	{
		m_downloader[i].setDir(&m_dir);
		m_downloader[i].start();
	}

	if (changed)
		emit modelStatusesChanged();
	emit synchronizeFinished(true);
}

void Synchronizer::setThreadCount(unsigned short count)
{
	m_threadCount = count;
}

unsigned short Synchronizer::threadCount()
{
	return m_threadCount;
}

void Synchronizer::slotThreadChangeModel()
{
	emit modelStatusesChanged();
}
