
#ifndef _CONSUMABLE_H_
#define _CONSUMABLE_H_

#include "Item.h"

class Consumable : public Item {
public:
	Consumable();
	virtual ~Consumable();

	virtual void ApplyEffect();
};

#endif
