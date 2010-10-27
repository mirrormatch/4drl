
#ifndef _MONSTER_TABLE_H_
#define _MONSTER_TABLE_H_

#include "GeneralIncludes.h"

class Monster;

class MonsterTable {
public:
	static MonsterTable* Instance();

	Monster* GenerateNewMonster();
	
protected:
	MonsterTable();
	~MonsterTable();
	void ConvertToReaper(Monster* m);
	string GetNamePrefix(int level);
	static MonsterTable* sm_instance;
};

#endif
