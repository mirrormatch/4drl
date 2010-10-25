
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

	virtual void SetIsTarget(bool isTarget);
	virtual int GetHP();
	virtual void SetHP(int hp);
	virtual void IncrementHP(int inc);
	virtual bool IsDead();
	virtual bool ShouldRemove();
	virtual void Kill();

	virtual int GetXPValue();

protected:
	int m_hp;
	int m_xpValue;
	bool m_isTarget;
};

#endif
