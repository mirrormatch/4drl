
#include "ArmorItem.h"

ArmorItem::ArmorItem() : Item() {
}

ArmorItem::~ArmorItem() {
}

int ArmorItem::GetAC() {
	return m_ac;
}

void ArmorItem::SetAC(int ac) {
	m_ac = ac;
}
