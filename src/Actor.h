

#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Entity.h"

class Actor : public Entity {
public:
	Actor();
	virtual ~Actor();

	virtual void Update();
	virtual void Activate();

	virtual void Advance(int x, int y);

	virtual int GetLevel();
	virtual void SetLevel(int lvl);
	virtual void IncrementLevel(int inc);
	virtual int GetHP();
	virtual void SetHP(int hp);
	virtual void IncrementHP(int inc);
	virtual int GetCurrentHP();
	virtual void SetCurrentHP(int chp);
	virtual void IncrementCurrentHP(int inc);
	virtual bool IsDead();
	virtual bool ShouldRemove();
	virtual void Kill();

	virtual int GetXPValue(Actor* p);
	virtual int GetXP();
	virtual void SetXP(int xp);
	virtual void IncrementXP(int inc);
	virtual int GetEyeRange();
	virtual int GetAttackRange();
	virtual void SetIsTarget(bool isTarget);
	virtual void AttackTarget();
	virtual void MoveTowardsTarget();
	virtual Actor* GetTarget();
	virtual void SetTarget(Actor* a);
	virtual int GetBaseDamage();

	virtual void SetEyeRange(int range);
	virtual void SetAttackRange(int range);
	virtual void SetBaseDamage(int dmg);

	virtual void SetHitRate(int hitRate);
	virtual int GetHitRate();

	virtual int GetSTR();
	virtual void SetSTR(int str);
	virtual int GetDEX();
	virtual void SetDEX(int dex);
	virtual int GetACC();
	virtual void SetACC(int acc);
	virtual int GetAC();
	virtual void SetAC(int ac);

	
protected:
	int m_xp;
	int m_hp;
	int m_currentHP;
	int m_str;
	int m_dex;
	int m_ac;
	int m_acc;
	int m_level;
	int m_eyeRange;
	int m_attackRange;
	int m_baseDamage;
	int m_hitRate;
	bool m_isTarget;
	Actor * m_target;
};

#endif
