#include "profilemodel.h"

using namespace VK;

ProfileModel::ProfileModel()
{
}

ProfileModel::~ProfileModel()
{
}

void ProfileModel::setFirstname(QString firstname)
{
	m_firstname = firstname;
}

QString ProfileModel::firstname()  const
{
	return m_firstname;
}

void ProfileModel::setLastname(QString lastname)
{
	m_lastname = lastname;
}

QString ProfileModel::lastname() const
{
	return m_lastname;
}
