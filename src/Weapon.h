

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Item.h"

class Weapon: public Item {
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
