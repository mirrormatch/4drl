
#include "Weapon.h"

Weapon::Weapon() : WearableItem() {
	m_class = E_WEAPON;
	m_range = 8;
	m_baseDamage = 4;
	SetDisplayName("Weapon of Combat Testing");
}

Weapon::~Weapon() {
}

int Weapon::GetRange() {
	return m_range;
}

int Weapon::GetBaseDamage() {
	return m_baseDamage;
}
