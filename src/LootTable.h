
#ifndef _LOOT_TABLE_H_
#define _LOOT_TABLE_H_

#include "GeneralIncludes.h"

class Item;
class Helm;
class BodyArmor;
class Pants;
class Weapon;
class Implant;
class Consumable;
class WearableItem;

enum StatTypes {
	STAT_STR,
	STAT_DEX,
	STAT_ACC,
	STAT_AC,
	NUM_BASIC_STATS
};

enum WeaponStatTypes {
	STAT_RANGE,
	STAT_DAMAGE,
	NUM_WEAPON_STATS
};

enum ConsumableStatTypes {
	STAT_HP,
	NUM_CONSUMABLE_STATS
};

class LootTable {
public:
	static LootTable* Instance();
	Item* GenerateLoot();

	Helm* GenerateHelm(int lvl);
	BodyArmor* GenerateBodyArmor(int lvl);
	Pants* GeneratePants(int lvl);
	Weapon* GenerateWeapon(int lvl);
	Implant* GenerateImplant(int lvl);
	Consumable* GenerateConsumable(int lvl);

protected:
	static LootTable* sm_instance;

	LootTable();
	virtual ~LootTable();

	string GetQualityIdentifier(int lvl);
	int CostForStat(StatTypes stat);
	int CostForWeaponStat(WeaponStatTypes stat);
	int CostForConsumableStat(ConsumableStatTypes stat);
	int GetPointsForLevel(int lvl);
	string PickStats(WearableItem* item, int points);
	string PickWeaponStats(Weapon* item, int points);
	string GetHelmVariant();
	string GetBodyArmorVariant();
	string GetPantsVariant();
	string GetImplantVariant();
	string GetConsumableVariant();
	string GetWeaponVariant();

};

#endif
