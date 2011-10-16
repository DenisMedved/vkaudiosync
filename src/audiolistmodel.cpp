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
	if (!m_audioList->empty() && m_audioList->size() >0)
	{
		return m_audioList->size();
	}
	return 0;
}

QVariant AudioListModel::data(const QModelIndex &index, int role ) const
{
	int row = index.row();
	QVariant variant = m_audioList->at(row).artist();
	qDebug() << variant;
	return variant;
}
