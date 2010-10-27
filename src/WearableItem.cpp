
#include "WearableItem.h"
#include "Player.h"
#include <sstream>


WearableItem::WearableItem() : Item(), m_ac(0), m_str(0), m_dex(0), m_acc(0) {
}

WearableItem::~WearableItem() {
}

int WearableItem::GetAC() {
	return m_ac;
}

void WearableItem::SetAC(int ac) {
	m_ac = ac;
}

int WearableItem::GetSTR() {
	return m_str;
}

void WearableItem::SetSTR(int str) {
	m_str = str;
}

int WearableItem::GetDEX() {
	return m_dex;
}

void WearableItem::SetDEX(int dex) {
	m_dex = dex;
}

int WearableItem::GetACC() {
	return m_acc;
}

void WearableItem::SetACC(int acc) {
	m_acc = acc;
}

void WearableItem::ApplyStatChanges(Player* p) {
	p->SetSTR(p->GetSTR() + GetSTR());
	p->SetDEX(p->GetDEX() + GetDEX());
	p->SetACC(p->GetACC() + GetACC());
	p->SetAC(p->GetAC() + GetAC());
}

void WearableItem::UnapplyStatChanges(Player* p) {
	p->SetSTR(p->GetSTR() - GetSTR());
	p->SetDEX(p->GetDEX() - GetDEX());
	p->SetACC(p->GetACC() - GetACC());
	p->SetAC(p->GetAC() - GetAC());
}

string WearableItem::GetInfoString() {
	stringstream s;
	if(m_str) {
		s << "STR +" << m_str << " ";
	}
	if(m_dex) {
		s << "DEX +" << m_dex << " ";
	}
	if(m_acc) {
		s << "ACC +" << m_acc << " ";
	}
	if(m_ac) {
		s << "AC +" << m_ac << " ";
	}
	s << "Req. Level: " << m_requiredLevel;

	return s.str();
}
