
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GeneralIncludes.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player();
	virtual ~Player();

	virtual void Update();
};

#endif
