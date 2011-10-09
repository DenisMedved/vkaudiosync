#ifndef PROFILEFACTORY_H
#define PROFILEFACTORY_H

#include "profilemodel.h"

namespace VK
{
class ProfileFactory
{
private:
    explicit ProfileFactory();
	~ProfileFactory();
public:
	void parseProfileModel() const;
};
}

#endif // PROFILEFACTORY_H
