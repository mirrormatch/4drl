
#include "LevelTable.h"
#include <math.h>
#include <sstream>
#include "DataManager.h"
#include "Player.h"

LevelTable* LevelTable::sm_instance = NULL;

LevelTable* LevelTable::Instance() {
	if(LevelTable::sm_instance == NULL) {
		LevelTable::sm_instance = new LevelTable();
	}

	return LevelTable::sm_instance;
}

LevelTable::LevelTable() {
}

LevelTable::~LevelTable() {
}

void LevelTable::CheckForLevelUp(Player* p) {
	int level = p->GetLevel();
	int required = GetXPForLevel(level + 1);
	if(p->GetXP() >= required) {
		p->SetLevel(level + 1);
		UpdatePlayerStats(p);
		stringstream s;
		s << "You are now level " << (level + 1);
		string status = s.str();
		DataManager::Instance()->AppendStatusString(status);
	}
}

void LevelTable::UpdatePlayerStats(Player* p) {
	// FIXME: This needs formulas, and eventually needs to be class specific
	p->SetSTR(p->GetSTR() + 2);
	p->SetDEX(p->GetDEX() + 1);
	p->SetACC(p->GetACC() + 2);
	p->SetCurrentHP(p->GetHP());
}

int LevelTable::GetXPForLevel(int level) {
	if(level == 1) {
		return 0;
	}

	float value = 0;
	float base = 25;
	for(int i = 1; i < level; i++) {
		value += base * pow(2.0, (i-1) / 4.0);
	}

	return (int)value;
}

