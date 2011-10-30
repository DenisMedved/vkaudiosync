#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QThread>
#include <QQueue>
#include <QUrl>
#include <QDir>
#include <QtNetwork>
#include <QFile>
#include <QDebug>

#include "../vk/audiomodel.h"

namespace VK {
class Downloader;
}

namespace Synch {
class Downloader : public QThread
{
    Q_OBJECT

protected:
    QDir *m_dir;
    QQueue<VK::AudioModel*> m_queue;
    QNetworkAccessManager *m_networkManager;
    QString m_name;

    bool ready();
    void run();
public:
    explicit Downloader(QObject *parent = 0);

    void setDir(QDir *dir);
    QDir* dir();
    void enqueue(VK::AudioModel *model);
    VK::AudioModel * dequeue();
signals:

protected slots:
    void finished(QNetworkReply* reply);
};
}
#endif // DOWNLOADER_H
