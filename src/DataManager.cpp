
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

DataManager* DataManager::sm_instance = NULL;

DataManager* DataManager::Instance() {
	if(DataManager::sm_instance == NULL) {
		DataManager::sm_instance = new DataManager();
		DataManager::sm_instance->LoadInfo();
	}

	return DataManager::sm_instance;
}

DataManager::DataManager() {
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
	Entrance* e = l->GetEntrance();
	m_player->SetPosition(e->GetX(), e->GetY());
}

void DataManager::GoToPrevLevel() {
	if(m_currentLevel > 0) {
		m_currentLevel--;
		Level* l = m_levels[m_currentLevel];
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
