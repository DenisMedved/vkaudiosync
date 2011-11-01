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

#include "audiolistmodel.h"

AudioListModel::AudioListModel(QObject *parent) :
	QAbstractListModel(parent)
{
}

AudioListModel::~AudioListModel()
{
}

void AudioListModel::setAudioList(QList<VK::AudioModel> audioList)
{
	m_audioList = audioList;
}


QList<VK::AudioModel>* AudioListModel::audioList()
{
	return &m_audioList;
}

void AudioListModel::setSettings(QSettings *settings)
{
	m_settings = settings;
}

QSettings* AudioListModel::settings()
{
	return m_settings;
}

int AudioListModel::rowCount(const QModelIndex&) const
{
	if (!m_audioList.empty() && m_audioList.size() > 0)
	{
		return m_audioList.size();
	}
	return 0;
}

QVariant AudioListModel::data(const QModelIndex &index, int role ) const
{
	int row = index.row();

	switch (role)
	{
	case AudioListModel::ROLE_ARTIST:
		return m_audioList.at(row).artist();

	case AudioListModel::ROLE_TITLE:
		return  m_audioList.at(row).title();

	case AudioListModel::ROLE_DURATION:
		return m_audioList.at(row).duration();

	case AudioListModel::ROLE_STATUS:
		return m_audioList.at(row).status();

	case AudioListModel::ROLE_PROGRESS:
		return m_audioList.at(row).progress();

	default:
		return QVariant();
	}
}
