
#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Entity.h"

class Monster : public Entity {
public:
	Monster();
	virtual ~Monster();

	virtual void Update();
	virtual void Activate();

	virtual void Advance(int x, int y);
};

#endif
