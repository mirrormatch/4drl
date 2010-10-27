
#include "LootTable.h"
#include "Item.h"
#include "Player.h"
#include "DataManager.h"
#include "Weapon.h"
#include "Helm.h"
#include "Pants.h"
#include "BodyArmor.h"
#include "Implant.h"
#include "Consumable.h"

LootTable* LootTable::sm_instance = NULL;

LootTable* LootTable::Instance() {
	if(LootTable::sm_instance == NULL) {
		LootTable::sm_instance = new LootTable();
	}

	return LootTable::sm_instance;
}

LootTable::LootTable() {
}

LootTable::~LootTable() {
}

Item* LootTable::GenerateLoot() {
	int playerLevel = DataManager::Instance()->GetPlayer()->GetLevel();
	int mod = (rand() % 5) - 1;
	int itemLevel = playerLevel + mod;
	if(itemLevel < 1) {
		itemLevel = 1;
	}
	switch(rand() % 20) {
		case 0:
		case 1:
			return GenerateHelm(itemLevel);
		case 2:
		case 3:
			return GenerateBodyArmor(itemLevel);
		case 4:
		case 5:
			return GeneratePants(itemLevel);
		case 6:
		case 7:
			return GenerateWeapon(itemLevel);
		case 8:
		case 9:
			return GenerateImplant(itemLevel);
		default:
			return GenerateConsumable(itemLevel);
	}
}

Helm* LootTable::GenerateHelm(int lvl) {
	Helm* toReturn = new Helm();

	string prefix = GetQualityIdentifier(lvl);
	string variant = GetHelmVariant();
	int points = GetPointsForLevel(lvl);
	int armorPoints = points * ((30 + (rand() % 20)) / 100.0);
	points = points - armorPoints;
	toReturn->SetAC(armorPoints);
	toReturn->SetRequiredLevel(lvl);
	string suffix = PickStats(toReturn, points);
	string name = prefix + " " + variant;
	if(suffix != "") {
		name = name + " of " + suffix;
	}
	toReturn->SetDisplayName(name);

	return toReturn;
}

BodyArmor* LootTable::GenerateBodyArmor(int lvl) {
	BodyArmor* toReturn = new BodyArmor();

	string prefix = GetQualityIdentifier(lvl);
	string variant = GetBodyArmorVariant();
	int points = GetPointsForLevel(lvl);
	int armorPoints = points * ((30 + (rand() % 20)) / 100.0);
	points = points - armorPoints;
	toReturn->SetAC(armorPoints);
	toReturn->SetRequiredLevel(lvl);
	string suffix = PickStats(toReturn, points);
	string name = prefix + " " + variant;
	if(suffix != "") {
		name = name + " of " + suffix;
	}
	toReturn->SetDisplayName(name);

	return toReturn;
}

Pants* LootTable::GeneratePants(int lvl) {
	Pants* toReturn = new Pants();

	string prefix = GetQualityIdentifier(lvl);
	string variant = GetPantsVariant();
	int points = GetPointsForLevel(lvl);
	int armorPoints = points * ((30 + (rand() % 20)) / 100.0);
	points = points - armorPoints;
	toReturn->SetAC(armorPoints);
	toReturn->SetRequiredLevel(lvl);
	string suffix = PickStats(toReturn, points);
	string name = prefix + " " + variant;
	if(suffix != "") {
		name = name + " of " + suffix;
	}
	toReturn->SetDisplayName(name);

	return toReturn;
}

Weapon* LootTable::GenerateWeapon(int lvl) {
	Weapon* toReturn = new Weapon();

	string prefix = GetQualityIdentifier(lvl);
	string variant = GetWeaponVariant();
	int points = GetPointsForLevel(lvl);
	int armorPoints = 0; // no AC on weapons
	points = points - armorPoints;
	toReturn->SetAC(armorPoints);
	toReturn->SetRequiredLevel(lvl);
	toReturn->SetBaseDamage(3 + (lvl - 1));
	toReturn->SetRange(4);
	string suffix = PickWeaponStats(toReturn, points);
	string name = prefix + " " + variant;
	if(suffix != "") {
		name = name + " of " + suffix;
	}
	toReturn->SetDisplayName(name);

	return toReturn;
}

Implant* LootTable::GenerateImplant(int lvl) {
	Implant* toReturn = new Implant();

	string prefix = GetQualityIdentifier(lvl);
	string variant = GetImplantVariant();
	int points = GetPointsForLevel(lvl);
	int armorPoints = 0; // no AC on implants
	points = points - armorPoints;
	toReturn->SetAC(armorPoints);
	toReturn->SetRequiredLevel(lvl);
	string suffix = PickStats(toReturn, points);
	string name = prefix + " " + variant;
	if(suffix != "") {
		name = name + " of " + suffix;
	}
	toReturn->SetDisplayName(name);

	return toReturn;
}

Consumable* LootTable::GenerateConsumable(int lvl) {
	Consumable* toReturn = new Consumable();

	string prefix = GetQualityIdentifier(lvl);
	string variant = GetConsumableVariant();
	int points = GetPointsForLevel(lvl);
	toReturn->SetRequiredLevel(lvl);
	toReturn->SetHP(points);
	string name = prefix + " " + variant;
	toReturn->SetItemID(1000 + lvl);
	toReturn->SetDisplayName(name);

	return toReturn;
}

int LootTable::GetPointsForLevel(int lvl) {
	return 9 + (lvl - 1) * 4;
}

string LootTable::GetQualityIdentifier(int lvl) {
	switch(lvl) {
		case 1:
			return "Trash";
		case 2:
			return "Burnt-Out";
		case 3:
			return "Cobbled";
		case 4:
			return "Damaged";
		case 5:
			return "Basic";
		case 6:
			return "Knock-Off";
		case 7:
			return "Dirty";
		case 8:
			return "Solid";
		case 9:
			return "Scratched";
		case 10:
			return "Standard";
		case 11:
			return "Prototype";
		case 12:
			return "Alloy";
		case 13:
			return "Energy";
		case 14:
			return "Carbon";
		case 15:
			return "Alien";
		case 16:
			return "Nanotech";
		default:
			return "Galactic";
	}
}

int LootTable::CostForStat(StatTypes stat) {
	switch(stat) {
		case STAT_STR:
			return 5;
		case STAT_DEX:
			return 5;
		case STAT_ACC:
			return 3;
		case STAT_AC:
			return 1;
		default:
			return 0;
	}
}

int LootTable::CostForWeaponStat(WeaponStatTypes stat) {
	switch(stat) {
		case STAT_RANGE:
			return 3;
		case STAT_DAMAGE:
			return 4;
		default:
			return 0;
	}
}

int LootTable::CostForConsumableStat(ConsumableStatTypes stat) {
	switch(stat) {
		case STAT_HP:
			return 5;
		default:
			return 0;
	}
}

string LootTable::GetHelmVariant() {
	switch(rand() % 5) {
		case 0:
			return "Visor";
		case 1:
			return "Helmet";
		case 2:
			return "Goggles";
		case 3:
			return "Mask";
		case 4:
			return "Hood";
		default:
			return "Helm";
	}
}

string LootTable::GetBodyArmorVariant() {
	switch(rand() % 5) {
		case 0:
			return "Vest";
		case 1:
			return "Armor";
		case 2:
			return "Suit";
		case 3:
			return "Flack Jacket";
		default:
		case 4:
			return "Sleeves";
	}
}

string LootTable::GetPantsVariant() {
	switch(rand() % 4) {
		case 0:
			return "Legs";
		case 1:
			return "Pants";
		case 2:
			return "Legplates";
		case 3:
		default:
			return "Tights";
	}
}

string LootTable::GetImplantVariant() {
	switch(rand() % 5) {
		case 0:
			return "Implant";
		case 1:
			return "Neurochip";
		case 2:
			return "Headjack";
		case 3:
			return "Memchip";
		case 4:
		default:
			return "Augmentor";
	}
}

string LootTable::GetConsumableVariant() {
	return "Healthpak";
}

string LootTable::GetWeaponVariant() {
	switch(rand() % 5) {
		case 0:
			return "Repeater";
		case 1:
			return "Rifle";
		case 2:
			return "Cannon";
		case 3:
			return "Disc Gun";
		case 4:
		default:
			return "Blaster";
	}
}

string LootTable::PickStats(WearableItem* item, int points) {
	StatTypes t = (StatTypes)(rand() % NUM_BASIC_STATS);
	int costPer = CostForStat(t);
	if(costPer / points) {
		switch(t) {
			case STAT_STR:
				item->SetSTR(costPer/points);
				return "Power";
			case STAT_DEX:
				item->SetDEX(costPer/points);
				return "Quickness";
			case STAT_ACC:
				item->SetACC(costPer/points);
				return "Accuracy";
			case STAT_AC:
				item->SetAC(item->GetAC() + (costPer/points));
				return "Defense";
			default:
				return "";
		}
	}
	return "";
}

string LootTable::PickWeaponStats(Weapon* item, int points) {
	WeaponStatTypes t = (WeaponStatTypes)(rand() % NUM_BASIC_STATS);
	int costPer = CostForWeaponStat(t);
	if(costPer / points) {
		switch(t) {
			case STAT_RANGE:
				item->SetRange(item->GetRange() + costPer/points);
				return "Distance";
			case STAT_DAMAGE:
				item->SetBaseDamage(item->GetBaseDamage() + costPer/points);
				return "Booming";
			default:
				return "";
		}
	}
	return "";
}
