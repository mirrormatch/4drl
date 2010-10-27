
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
	switch(rand() % 2) {
		case 0:
			// default, Xoich
			break;
		case 1:
			ConvertToReaper(m);
			break;
	}

	return m;
}

void MonsterTable::ConvertToReaper(Monster* m) {
	m->SetDisplayName("Reaper");
	m->SetDisplayChar('R');
	m->SetEyeRange(10);
	m->SetAttackRange(9);
	m->SetHP(m->GetLevel() * 2);
}
