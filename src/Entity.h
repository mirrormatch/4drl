
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

		virtual void SetPosition(int x, int y);
		virtual int GetX();
		virtual int GetY();

	protected:
		char m_dispChar;
		int m_dispFlags;
		int m_x;
		int m_y;
};

#endif
