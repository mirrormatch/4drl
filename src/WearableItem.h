
#ifndef _WEARABLE_ITEM_H_
#define _WEARABLE_ITEM_H_

#include "Item.h"

class Player;

class WearableItem : public Item {
public:
	WearableItem();
	virtual ~WearableItem();

	int GetAC();
	void SetAC(int ac);
	int GetSTR();
	void SetSTR(int str);
	int GetDEX();
	void SetDEX(int dex);
	int GetACC();
	void SetACC(int acc);

	void ApplyStatChanges(Player* p);
	void UnapplyStatChanges(Player* p);

protected:
	int m_ac;
	int m_str;
	int m_dex;
	int m_acc;
};

#endif
