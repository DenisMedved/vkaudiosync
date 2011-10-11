#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <QObject>
#include <QSettings>
#include <QDir>

namespace VK
{
class Synchronizer;
}

namespace Synch{
class Synchronizer : public QObject
{
    Q_OBJECT
private:
	QDir m_dir;
	QSettings* m_settings;

public:
    explicit Synchronizer(QObject *parent = 0);
	~Synchronizer();

	void setDir(QDir dir);
	QDir dir() const;

	void setSettings(QSettings * settings);
	QSettings* settings() const;

public slots:

signals:

};
}

#endif // SYNCHRONIZER_H
