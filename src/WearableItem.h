
#ifndef _WEARABLE_ITEM_H_
#define _WEARABLE_ITEM_H_

#include "Item.h"

class Player;

class WearableItem : public Item {
public:
	WearableItem();
	virtual ~WearableItem();

	virtual int GetAC();
	virtual void SetAC(int ac);
	virtual int GetSTR();
	virtual void SetSTR(int str);
	virtual int GetDEX();
	virtual void SetDEX(int dex);
	virtual int GetACC();
	virtual void SetACC(int acc);

	virtual void ApplyStatChanges(Player* p);
	virtual void UnapplyStatChanges(Player* p);

	virtual string GetInfoString();

protected:
	int m_ac;
	int m_str;
	int m_dex;
	int m_acc;
};

#endif
