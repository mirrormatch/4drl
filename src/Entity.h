
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "GeneralIncludes.h"

class Entity {
	public:
		Entity(char c, int dispflags);
		virtual ~Entity();

		virtual char GetDisplayChar();
		virtual int GetDisplayFlags();

		virtual void Update() = 0;

	protected:
		char m_dispChar;
		int m_dispFlags;
};

#endif
