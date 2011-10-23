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

#include "thread.h"

using namespace Synch;

Thread::Thread(QObject * parent) : QThread(parent)
{
    connect(&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void Thread::run()
{

    exec();
}

void Thread::enqueue(VK::AudioModel *model)
{
    m_queue.enqueue(model);
}

void Thread::setDir(QDir *dir)
{
    m_dir = dir;
}

void Thread::replyFinished(QNetworkReply *)
{

}
