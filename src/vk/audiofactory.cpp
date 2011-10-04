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
	QDomElement  root         = dom.firstChildElement(); // <response> root element
	QDomNode  audioElement = root.firstChildElement(); // <audio>
/*
 <aid>118272086</aid>
 <owner_id>3657181</owner_id>
 <artist>John Petrucci</artist>
 <title>Jaws of Life</title>
 <duration>449</duration>
 <url>http://cs4258.vkontakte.ru/u30445597/audio/3a40e57546f0.mp3</url>
*/
	 while(!audioElement.isNull()){
		/* AudioModel audioModel;
		 QDomE=  audioElement
				 .toElement()
				 .elementsByTagName("url")
				 .item(0)
				 .toElement()  //<url>
				 .text();

	      list << audioModel;
	      audioElement = audioElement.nextSibling()*/
	 }
}
