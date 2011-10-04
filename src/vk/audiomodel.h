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
