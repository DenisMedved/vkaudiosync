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

#ifndef AUDIOMODEL_H
#define AUDIOMODEL_H

#include <QString>
#include <QUrl>

namespace VK
{
    class AudioModel
    {
    private:
	    QString m_aid;
	    QString m_owner;
	    QString m_artist;
	    QString m_title;
	    unsigned short m_duration;
	    QUrl m_url;

    public:
	AudioModel();
	~AudioModel();

	QString aid() const;
	void setAid(QString newAid);

	QString owner() const;
	void setOwner(QString newOwner);

	QString artist() const;
	void setArtist(QString newArtist);

	QString title() const;
	void setTitle(QString newTitle);

	unsigned short duration() const;
	void setDuration(unsigned short newDuration);

	QUrl url() const;
	void setUrl(QUrl newUrl);
    };
}

#endif // AUDIOMODEL_H
