
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "Item.h"

class Inventory {
	public:
		Inventory();
		virtual ~Inventory();

		void AddItem(Item* toAdd);
		void RemoveItem(Item* toRemove);
		void RemoveItemAtIndex(unsigned int idx);

		const ItemList& GetItems();
		int NumItems();
		Item* ItemAtIndex(unsigned int idx);

	protected:
		ItemList m_items;
};

#endif
