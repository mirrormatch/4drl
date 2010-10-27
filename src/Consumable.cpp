
#include "Consumable.h"
#include "DataManager.h"
#include "Player.h"

Consumable::Consumable() : Item() {
	m_class = E_CONSUMABLE;
	m_canStack = true;
	m_stackSize = 1;
	m_itemID = 1;
	SetDisplayName("Consumable of Testing");
}

Consumable::~Consumable() {
}

void Consumable::ApplyEffect() {
	DataManager::Instance()->GetPlayer()->IncrementCurrentHP(m_hp);
	IncrementStack(-1);
}


void Consumable::SetHP(int hp) {
	m_hp = hp;
}

int Consumable::GetHP() {
	return m_hp;
}
