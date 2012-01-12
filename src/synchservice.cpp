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

#include "synchservice.h"


SynchService::SynchService(QObject *parent) :
	QObject(parent)
{
	setThreadsCount(THREADS);

	for (unsigned short i=0; i < THREADS; ++i) {
		m_pDownloadThreads[i] = new DownloadThread;
	}
}

SynchService::~SynchService()
{
	for (unsigned short i=0; i < THREADS; ++i) {
		delete m_pDownloadThreads[i];
	}
}

void SynchService::setDir(QDir *pdir)
{
	m_dir = pdir;
}

const QDir* SynchService::dir() const
{
	return m_dir;
}
void SynchService::setStatuses()
{
	if (m_dir->path().isEmpty() || !m_dir->isReadable())
		return;

	m_dir->setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );
	QFileInfoList files = m_dir->entryInfoList();

	int modelsCount = m_pAudioListModel->rowCount();
	QModelIndex modelIndex;
	bool modelFinded ;

	for (int i = 0; i < files.size(); ++i) {
		modelFinded = false;
		QFileInfo fileInfo = files.at(i);
		for (int m=0; m < modelsCount; ++m) {
			modelIndex = m_pAudioListModel->index(m);
			if (AudioItem::STATUS_UNDEFINED == m_pAudioListModel->data(modelIndex, AudioListModel::ROLE_STATUS).toInt()) {
				QString fullName = m_pAudioListModel->data(modelIndex, AudioListModel::ROLE_ARTIST).toString();
				fullName.append(" - ");
				fullName.append(m_pAudioListModel->data(modelIndex, AudioListModel::ROLE_TITLE).toString());
				if (fileInfo.exists() &&  fullName == fileInfo.baseName() && "mp3" == fileInfo.suffix()) {
					modelFinded = true;
					m_pAudioListModel->setData(
							modelIndex,
							QVariant(AudioItem::STATUS_SYNCHRONIZED),
							AudioListModel::ROLE_STATUS);
				}
			}
		}
		if (!modelFinded) {
			//upload to VK
		}
	}
}

void SynchService::synchronize()
{
	setStatuses();

	unsigned short threadIndex = 0;

	int modelsCount = m_pAudioListModel->rowCount();
	QModelIndex modelIndex;
	unsigned short status ;
	for (int m=0; m < modelsCount; ++m) {
		modelIndex = m_pAudioListModel->index(m);
		status = m_pAudioListModel->data(modelIndex, AudioListModel::ROLE_STATUS).toInt();
		if (AudioItem::STATUS_UNDEFINED == status
				|| AudioItem::STATUS_NEEDDOWNLOAD == status) {
			m_pAudioListModel->setData(
				modelIndex,
				QVariant(AudioItem::STATUS_NEEDDOWNLOAD),
				AudioListModel::ROLE_STATUS);

			if (threadIndex == THREADS) {
				threadIndex = 0;
			}

			m_pDownloadThreads[threadIndex]->enqueue(modelIndex);

			++threadIndex;
		}
	}

	for (unsigned short i=0; i < THREADS; ++i) {
		if (!m_pDownloadThreads[i]->queue()->isEmpty()) {
			m_pDownloadThreads[i]->setDir(m_dir);
			m_pDownloadThreads[i]->setAudioListModel(m_pAudioListModel);
			m_pDownloadThreads[i]->start();
		}
	}
}

void SynchService::setThreadsCount(unsigned short count)
{
	m_theadsCount = qMin(count,(unsigned short)100);
}

void SynchService::setAudioModel(AudioListModel *pAudioListModel)
{
	m_pAudioListModel = pAudioListModel;
}

void SynchService::synchFinished()
{

}
