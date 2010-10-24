
#ifndef _ENTRANCE_H_
#define _ENTRANCE_H_

#include "Entity.h"

class Entrance : public Entity {
	public:
		Entrance();
		virtual ~Entrance();

		void Update();
};

#endif
