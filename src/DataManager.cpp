
#include "DataManager.h"
#include "Level.h"
#include "Player.h"
#include "Exit.h"
#include "Entrance.h"
#include "Helm.h"
#include "BodyArmor.h"
#include "Pants.h"
#include "Weapon.h"
#include "Implant.h"
#include "Monster.h"
#include "Pathfinder.h"

DataManager* DataManager::sm_instance = NULL;

DataManager* DataManager::Instance() {
	if(DataManager::sm_instance == NULL) {
		DataManager::sm_instance = new DataManager();
		DataManager::sm_instance->LoadInfo();
	}

	return DataManager::sm_instance;
}

DataManager::DataManager() : m_statusLine("") {
}

DataManager::~DataManager() {
}

void DataManager::LoadInfo() {
	//FIXME: This needs to come from files
	m_classNames.push_back("Marine");
	m_classNames.push_back("Hacker");
	m_classNames.push_back("Librarian");
	m_classNames.push_back("Sniper");
	m_classNames.push_back("Engineer");
}

void DataManager::CreateNewGame() {
	m_player = new Player();
	m_player->CreateDefaults();
	Level* l = new Level(1);
	l->Generate(160, 48, 40);
	m_levels.push_back(l);
	m_currentLevel = 0;
	Pathfinder::Instance()->PopulateWithLevel(l);
	Entrance* e = l->GetEntrance();
	m_player->SetPosition(e->GetX(), e->GetY());
}

Level* DataManager::GetCurrentLevel() {
	return m_levels[m_currentLevel];
}

void DataManager::GoToNextLevel() {
	if(m_currentLevel == (int)m_levels.size() - 1) {
		// generate a new level and move there
			Level* l = new Level(GetCurrentLevel()->GetLevelNumber() + 1);
			l->Generate(160, 48, 40);
			m_levels.push_back(l);
	}
	m_currentLevel++;
	// move player
	Level* l = m_levels[m_currentLevel];
	Pathfinder::Instance()->PopulateWithLevel(l);
	Entrance* e = l->GetEntrance();
	m_player->SetPosition(e->GetX(), e->GetY());
}

void DataManager::GoToPrevLevel() {
	if(m_currentLevel > 0) {
		m_currentLevel--;
		Level* l = m_levels[m_currentLevel];
		Pathfinder::Instance()->PopulateWithLevel(l);
		Exit* e = l->GetExit();
		m_player->SetPosition(e->GetX(), e->GetY());
	}
}

Player* DataManager::GetPlayer() {
	return m_player;
}

const StringVector& DataManager::GetClassNames() {
	return m_classNames;
}

Item* DataManager::GenerateRandomItem() {
	switch(rand() % 5) {
		case 0:
			return new Helm();
		case 1:
			return new BodyArmor();
		case 2:
			return new Pants();
		case 3:
			return new Weapon();
		case 4:
			return new Implant();
		default:
			return NULL;
	}
}

Monster* DataManager::GenerateRandomMonster() {
	return new Monster();
}

void DataManager::AppendStatusString(string& toAppend) {
	if(m_statusLine == "") {
		m_statusLine = toAppend;
	}
	else {
		m_statusLine += " " + toAppend;
	}
	// chop the string down if we have to
	// ideally we'd have 2 lines or paging, but hey, 4drl
	if(m_statusLine.length() >= 78) {
		m_statusLine.erase(76, m_statusLine.length() - 1);
		m_statusLine += "...";
	}
}

string DataManager::GetStatusString() {
	return "(" + m_statusLine + ")";
}

void DataManager::ClearStatusString() {
	m_statusLine = "";
}

