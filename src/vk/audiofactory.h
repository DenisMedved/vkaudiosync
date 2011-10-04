#ifndef AUDIOFACTORY_H
#define AUDIOFACTORY_H

#include <QByteArray>

#include "audiomodel.h"

namespace VK
{
    class AudioFactory
    {
    private:
	    explicit AudioFactory();
	    ~AudioFactory();
    public:
	    static void parseAudioModel(const QByteArray *xml , QList<AudioModel> *list) ;

    };
}

#endif // AUDIOFACTORY_H
