#ifndef AUDIOLISTMODEL_H
#define AUDIOLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>

#include <vk/provider.h>

namespace VK
{
class AudioListModel;
}

class AudioListModel : public QAbstractListModel
{
    Q_OBJECT
private:
	QList<VK::AudioModel> *m_audioList;
	QSettings *m_settings;

public:
	static const int ROLE_ARTIST = 33;
	static const int ROLE_TITLE = 34;
	static const int ROLE_DURATION = 35;
	static const int ROLE_STATUS = 36;

    explicit AudioListModel(QObject *parent = 0);
	virtual ~AudioListModel();

	void setAudioList(QList<VK::AudioModel> *audioList);
	QList<VK::AudioModel>* audioList() const;

	void setSettings(QSettings *settings);
	QSettings* settings() ;

	virtual int rowCount(const QModelIndex&) const;
	virtual QVariant data(const QModelIndex &index, int role) const;

public slots:

signals:
};

#endif // AUDIOLISTMODEL_H
