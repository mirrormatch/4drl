
#include "Actor.h"
#include "Level.h"
#include "DataManager.h"

Actor::Actor() : 
		Entity('c', WHITE_BOLD, E_MONSTER), m_xp(0), m_hp(0), m_currentHP(0), 
		m_str(0), m_dex(0), m_ac(0), m_acc(0), m_level(0), m_eyeRange(0), 
		m_attackRange(0), m_baseDamage(0), m_hitRate(0), m_isTarget(false), 
		m_target(NULL) {
}

Actor::~Actor() {
}

void Actor::Update() {
}

void Actor::Activate() {
}

void Actor::Advance(int x, int y) {
	Level* l = DataManager::Instance()->GetCurrentLevel();
  if(l->IsSquareOpen(m_x + x, m_y + y, true)) {
    l->SquareAt(m_x, m_y)->entity = NULL;
    SetPosition(m_x + x, m_y + y);
    l->SquareAt(m_x, m_y)->entity = this;
  }
}

int Actor::GetLevel() {
	return m_level;
}

void Actor::SetLevel(int lvl) {
	m_level = lvl;
}

void Actor::IncrementLevel(int inc) {
	m_level += inc;
}

int Actor::GetHP() {
	return m_hp;
}

void Actor::SetHP(int hp) {
	m_hp = hp;
}

void Actor::IncrementHP(int inc) {
	m_hp += inc;
}

int Actor::GetCurrentHP() {
	return m_currentHP;
}

void Actor::SetCurrentHP(int chp) {
	m_currentHP = chp;
}

void Actor::IncrementCurrentHP(int inc) {
	m_currentHP += inc;
}

bool Actor::IsDead() {
	return m_currentHP <= 0;
}

bool Actor::ShouldRemove() {
	return IsDead();
}

void Actor::Kill() {
	// Do nothing by default
}

int Actor::GetXPValue(Actor* p) {
	int base = m_level * 5;
	float mod = (float)m_level / (float)p->GetLevel();
	base *= mod;

	return base;
}

int Actor::GetXP() {
	return m_xp;
}

void Actor::SetXP(int xp) {
	m_xp = xp;
}

void Actor::IncrementXP(int inc) {
	m_xp += inc;
}

int Actor::GetEyeRange() {
	return m_eyeRange;
}

int Actor::GetAttackRange() {
	return m_attackRange;
}

void Actor::AttackTarget() {

}

void Actor::MoveTowardsTarget() {
}

Actor* Actor::GetTarget() {
	return m_target;
}

void Actor::SetTarget(Actor* a) {
	m_target = a;
}

int Actor::GetBaseDamage() {
	return m_baseDamage;
}

void Actor::SetEyeRange(int range) {
	m_eyeRange = range;
}

void Actor::SetAttackRange(int range) {
	m_attackRange = range;
}

void Actor::SetBaseDamage(int dmg) {
	m_baseDamage = dmg;
}

void Actor::SetHitRate(int hitRate) {
	m_hitRate = hitRate;
}

int Actor::GetHitRate() {
	return m_hitRate;
}

int Actor::GetSTR() {
	return m_str;
}

void Actor::SetSTR(int str) {
	m_str = str;
}

int Actor::GetDEX() {
	return m_dex;
}

void Actor::SetDEX(int dex) {
	m_dex = dex;
}

int Actor::GetACC() {
	return m_acc;
}

void Actor::SetACC(int acc) {
	m_acc = acc;
}

int Actor::GetAC() {
	return m_ac;
}

void Actor::SetAC(int ac) {
	m_ac = ac;
}

void Actor::SetIsTarget(bool isTarget) {
	m_isTarget = isTarget;
}

