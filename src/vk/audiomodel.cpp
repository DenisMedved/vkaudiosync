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

#include "audiomodel.h"

#include <QUrl>
#include <QString>

using namespace VK;

AudioModel::AudioModel()
{
	m_status = STATUS_UNDEFINED;
}

AudioModel::~AudioModel()
{
}

QString AudioModel::aid() const
{
	return m_aid;
}

void AudioModel::setAid(QString newAid)
{
	m_aid = newAid;
}

QString AudioModel::owner() const
{
	return m_owner;
}

void AudioModel::setOwner(QString newOwner)
{
	m_owner = newOwner;
}

QString AudioModel::artist() const
{
	return m_artist;
}

void AudioModel::setArtist(QString newArtist)
{
	m_artist = newArtist;
}

QString AudioModel::title() const
{
	return m_title;
}

void AudioModel::setTitle(QString newTitle)
{
	m_title = newTitle;
}

unsigned short AudioModel::duration() const
{
	return m_duration;
}

void AudioModel::setDuration(unsigned short newDuration)
{
	m_duration = newDuration;
}

QUrl AudioModel::url() const
{
	return m_url;
}

void AudioModel::setUrl(QUrl newUrl)
{
	m_url = newUrl;
}

Status AudioModel::status()
{
	return m_status;
}

void AudioModel::setStatus(Status status)
{
	m_status = status;
}

QString AudioModel::path() const
{
	return m_path;
}

void AudioModel::setPath(QString file)
{
	m_path = file;
}

