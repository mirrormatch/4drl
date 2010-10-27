
#ifndef _CONSUMABLE_H_
#define _CONSUMABLE_H_

#include "Item.h"

class Consumable : public Item {
public:
	Consumable();
	virtual ~Consumable();

	virtual void SetHP(int hp);
	virtual int GetHP();

	virtual void ApplyEffect();
	virtual string GetInfoString();

protected:
	int m_hp;
};

#endif
