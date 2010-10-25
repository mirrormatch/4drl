
#include "Monster.h"
#include "DataManager.h"
#include "Level.h"
#include "Player.h"

Monster::Monster() : Entity('M', RED_BOLD, E_MONSTER) {
	m_isPassable = false;
	m_hp = 10;
	SetDisplayName("Tyrranasarus Test");
}

Monster::~Monster() {
}

void Monster::Kill() {
	Player* p = DataManager::Instance()->GetPlayer();
	p->SetTarget(NULL);
}

void Monster::Update() {
	if(IsDead()) {
		return;
	}
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
