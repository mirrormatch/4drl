
#ifndef _BODY_ARMOR_H_
#define _BODY_ARMOR_H_

#include "ArmorItem.h"

class BodyArmor : public ArmorItem {
public:
	BodyArmor();
	virtual ~BodyArmor();

	virtual void Update();
	virtual void Activate();
};

#endif
