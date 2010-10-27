
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "GeneralIncludes.h"

enum EntityClass {
	E_GENERIC,
	E_ENTRANCE,
	E_EXIT,
	E_PLAYER,
	E_CONSUMABLE,
	E_WEAPON,
	E_IMPLANT,
	E_HELM,
	E_BODY,
	E_LEGS,
	E_MONSTER
};

class Entity;
typedef list<Entity*> EntityList;

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
		virtual string& GetDisplayName();
		virtual void SetDisplayName(string name);
		virtual void SetDisplayChar(char ch);

		virtual bool IsPassable();
		virtual void SetIsPassable(bool val);

		virtual int DistanceTo(Entity* e);
		virtual bool ShouldRemove();
		virtual void Kill();

	protected:
		char m_dispChar;
		int m_dispFlags;
		int m_x;
		int m_y;
		EntityClass m_class;
		string m_displayName;
		bool m_isPassable;
};

#endif
