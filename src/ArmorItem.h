

#ifndef _ARMOR_ITEM_H_
#define _ARMOR_ITEM_H_

#include "Item.h"

class ArmorItem : public Item {
public:
	ArmorItem();
	virtual ~ArmorItem();

	int GetAC();
	void SetAC(int ac);

protected:
	int m_ac;
};

#endif
