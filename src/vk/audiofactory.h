#ifndef AUDIOFACTORY_H
#define AUDIOFACTORY_H

#include <QList>
#include <QString>
#include <QtXml>
#include "audiomodel.h"

namespace VK
{
    class AudioFactory
    {
    private:
	    explicit AudioFactory();
	    ~AudioFactory();
	    static  QList<AudioModel> models;
    public:
	    static QList<AudioModel> getAudioModels(QString xml);

    };
}

#endif // AUDIOFACTORY_H
