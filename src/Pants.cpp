
#include "Pants.h"

Pants::Pants() : ArmorItem() {
	m_class = E_LEGS;
	SetDisplayName("Pants of Testing");
	SetAC(3);
}

Pants::~Pants() {
}

void Pants::Update() {
}

void Pants::Activate() {
	ArmorItem::Activate();
}


