#include "downloader.h"

using namespace Synch;

Downloader::Downloader(QObject *parent) :
    QThread(parent)
{
}

void Downloader::enqueue(VK::AudioModel *model)
{
    m_queue.enqueue(model);
}

VK::AudioModel* Downloader::dequeue()
{
    return m_queue.dequeue();
}

bool Downloader::ready()
{
    return m_dir->exists() && !m_queue.isEmpty();
}

void Downloader::run()
{
    if (!ready())
        exit();
    qDebug() << "thread runing";
    m_networkManager = new QNetworkAccessManager(this);

    connect(m_networkManager,SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));

    VK::AudioModel *model;
    QNetworkRequest request;
    while (!m_queue.isEmpty())
    {
        model = dequeue();
        m_name = QString("%1 - %2.mp3")
                .arg(model->artist())
                .arg(model->title());

        request.setUrl(model->url());
        m_networkManager->get(request);
        //wait()
    }
    delete m_networkManager;


    qDebug() << "thread finished";
    exec();
}

void Downloader::finished(QNetworkReply* reply)
{
    QFile file;
    file.setFileName(m_dir->path() + QDir::separator() + m_name);
    if (file.isWritable() && file.open(QIODevice::WriteOnly))
    {
        file.write(reply->readAll());
        file.close();
    }
}

void Downloader::setDir(QDir *dir)
{
    m_dir = dir;
}

QDir* Downloader::dir()
{
    return m_dir;
}
