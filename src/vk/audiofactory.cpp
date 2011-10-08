#include <QList>
#include <QString>
#include <QByteArray>
#include <QtXml>

#include "audiomodel.h"
#include "audiofactory.h"

using namespace VK;

AudioFactory::AudioFactory()
{
}

AudioFactory::~AudioFactory()
{
}

void AudioFactory::parseAudioModel(const QByteArray *xml , QList<AudioModel> *list)
{
	QDomDocument dom;
	dom.setContent(*xml);
	QDomElement  root = dom.firstChildElement(); // <response> root element
	if (root.nodeName() == "response")
	{
		QDomNode  audioElement = root.firstChildElement(); // <audio>
		if (audioElement.nodeName() == "audio")
		{
			while (!audioElement.isNull())
			{
				AudioModel audioModel;
				QDomElement element = audioElement.toElement();

				audioModel.setAid(QString(element.elementsByTagName("aid").item(0).toElement().text()));
				audioModel.setOwner(QString(element.elementsByTagName("owner_id").item(0).toElement().text()));
				audioModel.setArtist(QString(element.elementsByTagName("artist").item(0).toElement().text()));
				audioModel.setTitle(QString(element.elementsByTagName("title").item(0).toElement().text()));
				audioModel.setDuration((unsigned int) element.elementsByTagName("duration").item(0).toElement().text().toInt());
				audioModel.setUrl(QUrl(element.elementsByTagName("url").item(0).toElement().text()));

				list->append(audioModel);
				audioElement = audioElement.nextSibling();
			}
		}
	}
}
