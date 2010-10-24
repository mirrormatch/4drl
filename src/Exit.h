
#ifndef _EXIT_H_
#define _EXIT_H_

#include "Entity.h"

class Exit : public Entity {
	public:
		Exit();
		virtual ~Exit();

		void Update();
};

#endif
