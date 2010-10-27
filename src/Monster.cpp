
#include "Monster.h"
#include "DataManager.h"
#include "Level.h"
#include "Player.h"
#include "Pathfinder.h"
#include "Sight.h"
#include <sstream>

Monster::Monster() : Entity('M', RED_BOLD, E_MONSTER), m_target(NULL) {
	m_isPassable = false;
	m_hp = 10;
	m_eyeRange = 7;
	m_attackRange = 4;
	m_baseDamage = 1;
	m_hitRate = 20;
	SetDisplayName("Xoich");
}

void Monster::SetLevel(int level) {
	m_level = level;
	SetHP(10 + 3 * (level - 1));
	m_baseDamage = 1 + (level - 1);
}

Monster::~Monster() {
}

void Monster::Kill() {
	Player* p = DataManager::Instance()->GetPlayer();
	p->SetTarget(NULL);
	p->IncrementXP(GetXPValue(p));
	if(!(rand() % 4)) {
		Item* loot = DataManager::Instance()->GenerateRandomItem();
		loot->SetPosition(m_x, m_y);
		Level* l = DataManager::Instance()->GetCurrentLevel();
		l->AddEntity(loot);
	}
}

void Monster::Update() {
	if(IsDead()) {
		return;
	}
	Player* p = DataManager::Instance()->GetPlayer();
	int dist = DistanceTo(p);
	if(!GetTarget()) {
		if(dist <= GetEyeRange() && Sight::Instance()->CanSee(this, p)) {
			SetTarget(p);
		}
		else {
			switch(rand() % 4) {
				case 0:
					Advance(1, 0);
					break;
				case 1:
					Advance(-1, 0);
					break;
				case 2:
					Advance(0, 1);
					break;
				case 4:
					Advance(0, -1);
					break;
			}
		}
	}
	if(GetTarget()) {
		if(dist <= GetAttackRange() && Sight::Instance()->CanSee(this, m_target)) {
			AttackTarget();
		}
		else {
			MoveTowardsTarget();
		}
	}
}

void Monster::AttackTarget() {
	int dist = DistanceTo(m_target);
	if(dist <= GetAttackRange()) {
		int damage = GetBaseDamage();
		int tlevel = m_target->GetLevel();
		int levdiff = m_level - tlevel;
		if(levdiff < 0) {
			damage += levdiff;
			if(damage <= 0) {
				damage = 1;
			}
		}
		int didhit = (rand() % 100) + (levdiff * 10);
		if(didhit >= m_hitRate) {
			int armorReduction = m_target->GetAC() / 5;
			damage -= armorReduction;
			if(damage < 1) {
				string status = GetDisplayName() + " does no damage.";
				DataManager::Instance()->AppendStatusString(status);
			}
			else {
				m_target->IncrementCurrentHP(-damage);
				stringstream s;
				s << GetDisplayName() << " hits for " << damage << ".";
				string status = s.str();
				DataManager::Instance()->AppendStatusString(status);
			}
		}
		else {
			string status = GetDisplayName() + " missed you.";
			DataManager::Instance()->AppendStatusString(status);
		}
	}
}

void Monster::MoveTowardsTarget() {
	Player* p = DataManager::Instance()->GetPlayer();
	Level* l = DataManager::Instance()->GetCurrentLevel();
	NodeList* path = Pathfinder::Instance()->PathBetweenPoints(m_x, m_y, p->GetX(), p->GetY());
	if(!path) {
		return;
	}
	Node* next = path->back();
	if(next) {
		l->SquareAt(m_x, m_y)->entity = NULL;
		SetPosition(next->GetX(), next->GetY());
		l->SquareAt(m_x, m_y)->entity = this;
	}
}

Player* Monster::GetTarget() {
	return m_target;
}

void Monster::SetTarget(Player* p) {
	m_target = p;
}

void Monster::Activate() {
}

void Monster::Advance(int xinc, int yinc) {
	Level* l = DataManager::Instance()->GetCurrentLevel();
	if(l->IsSquareOpen(m_x + xinc, m_y + yinc, true)) {
		l->SquareAt(m_x, m_y)->entity = NULL;
		SetPosition(m_x + xinc, m_y + yinc);
		l->SquareAt(m_x, m_y)->entity = this;
	}
}

int Monster::GetHP() {
	return m_hp;
}

void Monster::SetHP(int hp) {
	m_hp = hp;
}

void Monster::IncrementHP(int inc) {
	m_hp += inc;
}

bool Monster::IsDead() {
	return m_hp <= 0;
}

void Monster::SetIsTarget(bool isTarget) {
	m_isTarget = isTarget;
	if(isTarget) {
		m_dispFlags = MAGENTA_BOLD;
	}
	else {
		m_dispFlags = RED_BOLD;
	}
}

bool Monster::ShouldRemove() {
	return IsDead();
}

int Monster::GetXPValue(Player* p) {
	int base = m_level * 5;
	float mod = (float)m_level / (float)p->GetLevel();
	base *= mod;
	return base;
}

int Monster::GetEyeRange() {
	return m_eyeRange;
}

int Monster::GetAttackRange() {
	return m_attackRange;
}

int Monster::GetBaseDamage() {
	return m_baseDamage;
}

void Monster::SetEyeRange(int range) {
	m_eyeRange = range;
}

void Monster::SetAttackRange(int range) {
	m_attackRange = range;
}

int Monster::GetLevel() {
	return m_level;
}

void Monster::SetBaseDamage(int dmg) {
	m_baseDamage = dmg;
}

void Monster::SetHitRate(int hitRate) {
	m_hitRate = hitRate;
}

int Monster::GetHitRate() {
	return m_hitRate;
}
