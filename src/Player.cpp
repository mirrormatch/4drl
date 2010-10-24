
#include "Player.h"
#include "DataManager.h"
#include "Level.h"

Player::Player() : Entity('@', YELLOW_BOLD) {
}

Player::~Player() {
}

void Player::Update() {
}

bool Player::Advance(int xinc, int yinc) {
	Level* l = DataManager::Instance()->GetCurrentLevel();
	if(l->IsSquareOpen(m_x + xinc, m_y + yinc)) {
		SetPosition(m_x + xinc, m_y + yinc);
		//FIXME: interact with items on the board
		return true;
	}

	return false;
}
