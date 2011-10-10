#include "synchronizer.h"

using namespace Synch;

Synchronizer::Synchronizer(QObject *parent) :
    QObject(parent)
{
}

Synchronizer::~Synchronizer()
{
}

void Synchronizer::setDir(QDir dir)
{
	m_dir = dir;
}

QDir Synchronizer::dir() const
{
	return m_dir;
}

void Synchronizer::setSettings(QSettings *settings)
{
	m_settings = settings;
}

QSettings* Synchronizer::settings() const
{
	return m_settings;
}
