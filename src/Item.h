
#ifndef _ITEM_H_
#define _ITEM_H_

#include "GeneralIncludes.h"
#include "Entity.h"

class Item;
typedef list<Item*> ItemList;

class Item : public Entity {
	public:
		Item();
		virtual ~Item();

		virtual void Update();
		virtual void Activate();
};

#endif
