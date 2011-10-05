#include "audiomodel.h"

#include <QUrl>
#include <QString>

using namespace VK;

AudioModel::AudioModel()
{
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
