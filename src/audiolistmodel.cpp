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

void AudioListModel::setAudioList(QList<VK::AudioModel> *audioList)
{
	m_audioList = audioList;
}


QList<VK::AudioModel>* AudioListModel::audioList()
{
	return m_audioList;
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
	if (!m_audioList->empty() && m_audioList->size() > 0)
	{
		return m_audioList->size();
	}
	return 0;
}

QVariant AudioListModel::data(const QModelIndex &index, int role ) const
{
	int row = index.row();

	switch (role)
	{
	case AudioListModel::ROLE_ARTIST:
		return m_audioList->at(row).artist();

	case AudioListModel::ROLE_TITLE:
		return  m_audioList->at(row).title();

	case AudioListModel::ROLE_DURATION:
		return m_audioList->at(row).duration();

	case AudioListModel::ROLE_STATUS:
		return m_audioList->at(row).status();

	case AudioListModel::ROLE_PROGRESS:
		return m_audioList->at(row).progress();

	default:
		return QVariant();
	}
}

bool AudioListModel::setData ( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
	bool result = false;

	switch(role) {
	case AudioListModel::ROLE_PROGRESS:
		(*m_audioList)[index.row()].setProgress(value.toInt());
		break;

	default:
		break;
	}

	/*
	 * The dataChanged() signal should be emitted if the data was successfully set.
	 */
	if (result)
		emit dataChanged(index,index);

	return result;
}

void AudioListModel::resetStatuses()
{
	QList<VK::AudioModel>::iterator iterator;
	for (iterator = m_audioList->begin(); iterator != m_audioList->end(); ++iterator)
	{
		iterator->setStatus(VK::AudioModel::STATUS_UNDEFINED);
	}
	unsigned int count = m_audioList->size();

	if (count > 0)
		emit dataChanged(index(0),index(count-1));

}
