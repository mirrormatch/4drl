
#include "Weapon.h"

Weapon::Weapon() : Item() {
	m_class = E_WEAPON;
	SetDisplayName("Weapon of Testing");
}

Weapon::~Weapon() {
}
