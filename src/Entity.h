
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "GeneralIncludes.h"

enum EntityClass {
	E_GENERIC,
	E_ENTRANCE,
	E_EXIT,
	E_PLAYER
};

class Entity {
	public:
		Entity(char c, int dispflags, EntityClass cls);
		virtual ~Entity();

		virtual char GetDisplayChar();
		virtual int GetDisplayFlags();

		virtual void Update() = 0;
		virtual void Activate() = 0;

		virtual void SetPosition(int x, int y);
		virtual int GetX();
		virtual int GetY();

		virtual EntityClass GetClass();

	protected:
		char m_dispChar;
		int m_dispFlags;
		int m_x;
		int m_y;
		EntityClass m_class;
};

#endif
