
#include "Item.h"
#include "DataManager.h"
#include "Player.h"
#include "Inventory.h"
#include "Level.h"

Item::Item() : Entity('i', CYAN_BOLD, E_GENERIC), m_canStack(false), m_stackSize(0), m_requiredLevel(1), m_itemID(0) {
	SetDisplayName("Temp Item of Boldness");
}

Item::~Item() {
}

void Item::Update() {
}

void Item::Activate() {
	Inventory& inv = DataManager::Instance()->GetPlayer()->GetInventory();
	inv.AddItem(this);
	DataManager::Instance()->GetCurrentLevel()->RemoveEntity(this);
	string status = "Picked up " + this->GetDisplayName();
	DataManager::Instance()->AppendStatusString(status);
}

bool Item::CanStack() {
	return m_canStack;
}

int Item::GetStackSize() {
	return m_stackSize;
}

void Item::IncrementStack(int inc) {
	m_stackSize += inc;
	if(m_stackSize < 0) {
		m_stackSize = 0;
	}
}

int Item::GetRequiredLevel() {
	return m_requiredLevel;
}

void Item::SetRequiredLevel(int lvl) {
	m_requiredLevel = lvl;
}

bool Item::CanUse() {
	Player* p = DataManager::Instance()->GetPlayer();
	return p->GetLevel() >= m_requiredLevel;
}

int Item::GetItemID() {
	return m_itemID;
}

void Item::SetItemID(int id) {
	m_itemID = id;
}

string Item::GetInfoString() {
	return "This is an item of no value.";
}
