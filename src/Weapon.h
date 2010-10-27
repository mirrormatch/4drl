

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "WearableItem.h"

class Weapon: public WearableItem {
public:
	Weapon();
	virtual ~Weapon();

	virtual int GetRange();
	virtual int GetBaseDamage();

protected:
	int m_range;
	int m_baseDamage;
};

#endif
