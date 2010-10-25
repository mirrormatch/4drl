
#ifndef _PANTS_H_
#define _PANTS_H_

#include "ArmorItem.h"

class Pants : public ArmorItem {
public:
	Pants();
	virtual ~Pants();

	virtual void Update();
	virtual void Activate();
};

#endif
