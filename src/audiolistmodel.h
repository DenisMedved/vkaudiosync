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

#ifndef AUDIOLISTMODEL_H
#define AUDIOLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QList>
#include <QByteArray>
#include <QtXml>

#include "audioitem.h"

class AudioListModel : public QAbstractListModel
{
	Q_OBJECT

private:
	QList<AudioItem> *m_pItems;

public:
	static const int ROLE_ARTIST   = 33;
	static const int ROLE_TITLE    = 34;
	static const int ROLE_DURATION = 35;
	static const int ROLE_STATUS   = 36;
	static const int ROLE_PROGRESS = 37;
	static const int ROLE_URL	   = 38;

	explicit AudioListModel(QObject *parent = 0);
	virtual ~AudioListModel();

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual void resetStatuses();

	void parseXml(const QByteArray &xml);
	void clear();

};

#endif // AUDIOLISTMODEL_H
