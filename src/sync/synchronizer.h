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

#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <QObject>
#include <QSettings>
#include <QDir>

#include "../vk/audiomodel.h"

namespace VK
{
class Synchronizer;
}

namespace Synch{
class Synchronizer : public QObject
{
	Q_OBJECT
private:
	QDir m_dir;
	QSettings* m_settings;
	QList<VK::AudioModel>* m_audioList;

public:
	explicit Synchronizer(QObject *parent = 0);
	~Synchronizer();

	void setDir(QDir dir);
	QDir dir() const;

	void setSettings(QSettings * settings);
	QSettings* settings() const;

	void setAudioList(QList<VK::AudioModel>* list);

	void synchronize();

public slots:

signals:
	void modelStatusesChanged();
};
}

#endif // SYNCHRONIZER_H
