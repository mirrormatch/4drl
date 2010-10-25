
#include "Helm.h"

Helm::Helm() : ArmorItem() {
	m_class = E_HELM;
	SetDisplayName("Helm of Testing");
	SetAC(2);
}

Helm::~Helm() {
}

void Helm::Update() {
}

void Helm::Activate() {
	ArmorItem::Activate();
}


