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
#include <QDebug>
using namespace Synch;

Synchronizer::Synchronizer(QObject *parent) :
    QObject(parent)
{
}

Synchronizer::~Synchronizer()
{
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
	qDebug() << list->at(0).artist() + " - " + list->at(1).title();
}

void Synchronizer::synchronize()
{
	if (m_dir.path().isEmpty() || !m_dir.isReadable())
		return;

	m_dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );
	QFileInfoList files = m_dir.entryInfoList();
	for (int i = 0; i < files.size(); ++i)
	{
	    QFileInfo fileInfo = files.at(i);
	    //mi as model index

	 /*
	   //TODO: set statuses for models
	   for ( int mi=0; mi < m_audioList->size(); ++mi )
	    {
		    VK::AudioModel* model = m_audioList->takeAt(mi);
		    if (VK::STATUS_UNDEFINED == model->status())
		    {
			    QString fullName = model->artist();
			    fullName.append(" - ");
			    fullName.append(model->title());
			    if (fileInfo.exists() &&  fullName == fileInfo.baseName() && "mp3" == fileInfo.suffix())
			    {
				    model->setStatus(VK::STATUS_SYNCHRONIZED);
			    }
		    }
	    }*/
	    qDebug() << fileInfo.fileName();
	}
}
