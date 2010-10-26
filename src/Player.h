
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GeneralIncludes.h"
#include "Entity.h"
#include "Inventory.h"

class ArmorItem;
class Item;
class Weapon;
class Implant;
class Monster;

class Player : public Entity {
public:
	Player();
	virtual ~Player();

	virtual bool Advance(int xinc, int yinc);
	virtual void Update();
	virtual void Activate();

	virtual void CreateDefaults();
	virtual string& GetName();
	virtual void SetName(string name);
	virtual string& GetTitle();
	virtual void SetTitle(string title);
	virtual string& GetFullName();
	virtual int GetXP();
	virtual void SetXP(int xp);
	virtual void IncrementXP(int inc);
	virtual int GetLevel();
	virtual void SetLevel(int lvl);
	virtual void IncrementLevel(int inc);
	virtual int GetHP();
	virtual void SetHP(int hp);
	virtual void IncrementHP(int inc);
	virtual int GetCurrentHP();
	virtual void SetCurrentHP(int chp);
	virtual void IncrementCurrentHP(int inc);
	virtual int GetSTR();
	virtual void SetSTR(int str);
	virtual int GetDEX();
	virtual void SetDEX(int dex);
	virtual int GetACC();
	virtual void SetACC(int acc);
	virtual int GetAC();
	virtual void SetAC(int ac);

	Inventory& GetInventory();
	ArmorItem* GetHeadItem();
	ArmorItem* GetBodyItem();
	ArmorItem* GetLegsItem();
	Weapon* GetWeaponItem();
	Implant* GetImplantItem();
	void SetHeadItem(ArmorItem* newItem);
	void SetBodyItem(ArmorItem* newItem);
	void SetLegsItem(ArmorItem* newItem);
	void SetWeaponItem(Weapon* newItem);
	void SetImplantItem(Implant* newItem);
	void ReturnHeadItemToInventory();
	void ReturnBodyItemToInventory();
	void ReturnLegsItemToInventory();
	void ReturnWeaponItemToInventory();
	void ReturnImplantItemToInventory();
	void SetTarget(Monster* target);
	
	bool IsDead();

	virtual void AttackTarget();

protected:
	string m_name;
	string m_title;
	string m_fullName;
	int m_xp;
	int m_hp;
	int m_currentHP;
	int m_str;
	int m_dex;
	int m_ac;
	int m_acc;
	int m_level;
	Inventory m_inventory;
	ArmorItem* m_headSlot;
	ArmorItem* m_bodySlot;
	ArmorItem* m_legsSlot;
	Weapon* m_weaponSlot;
	Implant* m_implantSlot;
	Monster* m_target;
};

#endif
