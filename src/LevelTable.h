
#ifndef _LEVEL_TABLE_H_
#define _LEVEL_TABLE_H_

#include "GeneralIncludes.h"

class Player;

class LevelTable {
public:
	static LevelTable* Instance();

	void CheckForLevelUp(Player* p);

protected:
  int GetXPForLevel(int level);
	void UpdatePlayerStats(Player* p);
	LevelTable();
	virtual ~LevelTable();

	static LevelTable* sm_instance;
};

#endif
