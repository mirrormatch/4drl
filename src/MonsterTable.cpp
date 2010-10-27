
#include "MonsterTable.h"
#include "Monster.h"
#include "DataManager.h"
#include "Player.h"

MonsterTable* MonsterTable::sm_instance = NULL;

MonsterTable* MonsterTable::Instance() {
	if(MonsterTable::sm_instance == NULL) {
		MonsterTable::sm_instance = new MonsterTable();
	}
	return MonsterTable::sm_instance;
}

MonsterTable::MonsterTable() {
}

MonsterTable::~MonsterTable() {
}

Monster* MonsterTable::GenerateNewMonster() {
	Monster* m = new Monster();
	int baseLevel = DataManager::Instance()->GetPlayer()->GetLevel();
	int diff = (rand() % 5) - 2;
	int level = baseLevel + diff;
	if(level < 1) {
		level = 1;
	}
	m->SetLevel(level);
	string newName;
	switch(rand() % 2) {
		case 0:
			// default, Xoich
			newName = GetNamePrefix(m->GetLevel()) + " Xoich";
			m->SetDisplayName(newName);
			break;
		case 1:
			ConvertToReaper(m);
			break;
	}

	return m;
}

void MonsterTable::ConvertToReaper(Monster* m) {
	string newName = GetNamePrefix(m->GetLevel()) + " Reaper";
	m->SetDisplayName(newName);
	m->SetDisplayChar('R');
	m->SetEyeRange(10);
	m->SetAttackRange(8);
	m->SetHP(m->GetLevel() * 2);
}

string MonsterTable::GetNamePrefix(int level) {
	switch(level) {
		case 1:
			return "Weak";
		case 2:
			return "Sloth";
		case 3:
			return "Scared";
		case 4:
			return "Dumb";
		case 5:
			return "Simple";
		case 6:
			return "Better";
		case 7:
			return "Not-Awful";
		case 8:
			return "Kinda Lazy";
		case 9:
			return "Light";
		case 10:
			return "Normal";
		case 11:
			return "Fit";
		case 12:
			return "Fancy";
		case 13:
			return "Hardened";
		case 14:
			return "Experienced";
		case 15:
			return "Strong";
		case 16:
			return "Deadly";
		default:
			return "Death";
	}
}
