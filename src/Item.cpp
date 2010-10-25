
#include "Item.h"
#include "DataManager.h"
#include "Player.h"
#include "Inventory.h"
#include "Level.h"

Item::Item() : Entity('i', CYAN_BOLD, E_GENERIC) {
	SetDisplayName("Temp Item of Boldness");
}

Item::~Item() {
}

void Item::Update() {
}

void Item::Activate() {
	Inventory& inv = DataManager::Instance()->GetPlayer()->GetInventory();
	inv.AddItem(this);
	DataManager::Instance()->GetCurrentLevel()->SquareAt(m_x, m_y)->entity = NULL;
}

