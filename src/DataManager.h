
#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include "GeneralIncludes.h"

class Level;
class Player;

typedef vector<Level*> LevelVector;

class DataManager {
public:
	static DataManager* Instance();

	void CreateNewGame();
	Level* GetCurrentLevel();
	void GoToNextLevel();
	void GoToPrevLevel();
	Player* GetPlayer();

	//FIXME: Implement these
	//void LoadGame(string& path);
	//void SaveGame(string& path);

private:
	DataManager();
	~DataManager();

	LevelVector m_levels;
	Player* m_player;
	int m_currentLevel;

	static DataManager* sm_instance;
};

#endif
