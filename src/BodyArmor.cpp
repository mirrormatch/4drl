
#include "BodyArmor.h"

BodyArmor::BodyArmor() : ArmorItem() {
	m_class = E_BODY;
	SetDisplayName("Body Armor of Testing");
	SetAC(4);
}

BodyArmor::~BodyArmor() {
}

void BodyArmor::Update() {
}

void BodyArmor::Activate() {
	ArmorItem::Activate();
}


