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

#ifndef AUDIOFACTORY_H
#define AUDIOFACTORY_H

#include <QList>
#include <QString>
#include <QByteArray>
#include <QtXml>
#include "audiomodel.h"

namespace VK
{
	class AudioFactory
	{
	private:
		explicit AudioFactory();
		~AudioFactory();
	public:
		static void parseAudioModel(const QByteArray *xml , QList<AudioModel> *list) ;

	};
}

#endif // AUDIOFACTORY_H
