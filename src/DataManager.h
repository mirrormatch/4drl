
#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "GeneralIncludes.h"

class Item;
class Level;
class Player;
class Monster;

typedef vector<Level*> LevelVector;

class DataManager {
public:
	static DataManager* Instance();

	void CreateNewGame();
	Level* GetCurrentLevel();
	void GoToNextLevel();
	void GoToPrevLevel();
	Player* GetPlayer();
	void LoadInfo();

	const StringVector& GetClassNames();

	Item* GenerateRandomItem();
	Monster* GenerateRandomMonster();

	void AppendStatusString(string& toAppend);
	string GetStatusString();
	void ClearStatusString();

	//FIXME: Implement these
	//void LoadGame(string& path);
	//void SaveGame(string& path);

	void ResetAllData();
	void DeleteAllData();

private:
	DataManager();
	~DataManager();

	LevelVector m_levels;
	Player* m_player;
	int m_currentLevel;
	StringVector m_classNames;
	string m_statusLine;

	static DataManager* sm_instance;
};

#endif
