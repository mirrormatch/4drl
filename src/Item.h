
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
		virtual bool CanStack();
		virtual int GetStackSize();
		virtual void IncrementStack(int inc);
		virtual int GetRequiredLevel();
		virtual bool CanUse();
		virtual int GetItemID();
	
	protected:
		bool m_canStack;
		int m_stackSize;
		int m_requiredLevel;
		int m_itemID;
};

#endif
