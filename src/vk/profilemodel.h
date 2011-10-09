#ifndef PROFILEMODEL_H
#define PROFILEMODEL_H

#include <QString>

namespace VK
{
class ProfileModel
{
private:
	QString m_firstname;
	QString m_lastname;
public:
    explicit ProfileModel();
	~ProfileModel();

	void setFirstname(QString firstname);
	QString firstname() const;

	void setLastname(QString lastname);
	QString lastname() const;


};
}

#endif // PROFILEMODEL_H
