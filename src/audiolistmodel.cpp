
#include <QDebug>
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


QList<VK::AudioModel>* AudioListModel::audioList() const
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
