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

#ifndef THREAD_H
#define THREAD_H

#include <QtNetwork>
#include <QThread>
#include <QDir>
#include <QQueue>
#include <QObject>

#include "../vk/audiomodel.h"

namespace Synch
{
class Thread : public QThread
{
private:
    QDir *m_dir;
    QQueue<VK::AudioModel*> m_queue;
    QNetworkAccessManager m_networkAccessManager;

public:
    Thread(QObject * parent = 0);
    void enqueue(VK::AudioModel *model);
    void setDir(QDir *dir);
    void run();

private slots:
    void replyFinished(QNetworkReply*);

};
}

#endif // THREAD_H
