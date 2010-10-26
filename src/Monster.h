
#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "Entity.h"

class Player;

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
	virtual int GetEyeRange();
	virtual int GetAttackRange();
	virtual void AttackTarget();
	virtual void MoveTowardsTarget();
	virtual Player* GetTarget();
	virtual void SetTarget(Player* p);
	virtual int GetBaseDamage();

protected:
	int m_hp;
	int m_xpValue;
	bool m_isTarget;
	int m_eyeRange;
	int m_attackRange;
	int m_baseDamage;
	Player* m_target;
};

#endif
