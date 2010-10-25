
#include "Monster.h"
#include "DataManager.h"
#include "Level.h"

Monster::Monster() : Entity('M', RED_BOLD, E_MONSTER) {
	m_isPassable = false;
}

Monster::~Monster() {
}

void Monster::Update() {
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
