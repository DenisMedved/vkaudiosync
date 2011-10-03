#include <QList>
#include <QString>
#include "audiomodel.h"
#include "audiofactory.h"

using namespace VK;

AudioFactory::AudioFactory()
{
}
AudioFactory::~AudioFactory()
{
}
static QList<AudioModel> getAudioModels(QString xml)
{

	QDomDocument dom;
	dom.setContent(xml);
	QDomElement  root         = dom.firstChildElement(); // <response> root element
	QDomNode  audioElement = root.firstChildElement(); // <audio>

	 while(!audioElement.isNull()){
	    /*
	     QString url =  audioElement
				 .toElement()
				 .elementsByTagName("url")
				 .item(0)
				 .toElement()  //<url>
				 .text();
	      list.append(url);
	      audioElement = audioElement.nextSibling()
	      */
	 }
}
