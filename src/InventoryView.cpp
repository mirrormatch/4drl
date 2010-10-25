
#include "InventoryView.h"
#include "GameState.h"
#include "Player.h"
#include "Inventory.h"
#include "DataManager.h"
#include "Item.h"
#include "ArmorItem.h"
#include "Weapon.h"
#include "Implant.h"
#include <sstream>

InventoryView::InventoryView(GameState* gs, int w, int h) :
	View(gs, w, h), m_inInventoryArea(true), m_selectIdx(0) {
}

InventoryView::~InventoryView() {
}

bool InventoryView::RequestInput() {
	int ch = getch();
	Player* p = DataManager::Instance()->GetPlayer();
	Inventory& inv = p->GetInventory();
	switch(ch) {
		case KEY_UP:
			m_selectIdx--;
			if(m_selectIdx < 0) {
				m_selectIdx = 0;
			}
		break;
		case KEY_DOWN:
			m_selectIdx++;
			if(m_inInventoryArea) {
				if(m_selectIdx >= inv.NumItems()) {
					m_selectIdx = inv.NumItems() - 1;
				}
			}
			else {
				if(m_selectIdx > 4) {
					m_selectIdx = 4;
				}
			}
		break;
		case KEY_LEFT:
			m_inInventoryArea = !m_inInventoryArea;
			m_selectIdx = 0;
		break;
		case KEY_RIGHT:
			m_inInventoryArea = !m_inInventoryArea;
			m_selectIdx = 0;
		break;
		case '\n':
		case KEY_ENTER:
			HandleItemSelection();
			break;
		case 27:
			m_parent->ChangeState(GAME_STATE_MAIN);
			break;
	}
	return false;
}

void InventoryView::HandleItemSelection() {
	Player* p = DataManager::Instance()->GetPlayer();
	Inventory& inv = p->GetInventory();
	if(m_inInventoryArea) {
		if(inv.NumItems() > 0) {
			Item* toUse = inv.ItemAtIndex(m_selectIdx);
			Item* oldItem = NULL;
			switch(toUse->GetClass()) {
				case E_HELM:
					inv.RemoveItem(toUse);
					oldItem = p->GetHeadItem();
					p->SetHeadItem((ArmorItem*)toUse);
					if(oldItem) {
						inv.AddItem(oldItem);
					}
					break;
				case E_BODY:
					inv.RemoveItem(toUse);
					oldItem = p->GetBodyItem();
					p->SetBodyItem((ArmorItem*)toUse);
					if(oldItem) {
						inv.AddItem(oldItem);
					}
					break;
				case E_LEGS:
					inv.RemoveItem(toUse);
					oldItem = p->GetLegsItem();
					p->SetLegsItem((ArmorItem*)toUse);
					if(oldItem) {
						inv.AddItem(oldItem);
					}
					break;
				case E_WEAPON:
					inv.RemoveItem(toUse);
					oldItem = p->GetWeaponItem();
					p->SetWeaponItem((Weapon*)toUse);
					if(oldItem) {
						inv.AddItem(oldItem);
					}
					break;
				case E_IMPLANT:
					inv.RemoveItem(toUse);
					oldItem = p->GetImplantItem();
					p->SetImplantItem((Implant*)toUse);
					if(oldItem) {
						inv.AddItem(oldItem);
					}
					break;
				default:
					break;
			}
		}
	}
	else {
		switch(m_selectIdx) {
			case 0:
				p->ReturnHeadItemToInventory();
				break;
			case 1:
				p->ReturnBodyItemToInventory();
				break;
			case 2:
				p->ReturnLegsItemToInventory();
				break;
			case 3:
				p->ReturnWeaponItemToInventory();
				break;
			case 4:
				p->ReturnImplantItemToInventory();
				break;
		}
	}
}

void InventoryView::Inititalize() {
	m_inInventoryArea = true;
	m_selectIdx = 0;
}

void InventoryView::Update() {
	Clear();
	for(int y = 0; y < 24; y++) {
		SetCharAt(49, y, '|', WHITE);
	}
	string toDraw = "Equipped Items";
	int wd2 = toDraw.length() / 2;
	SetStringAt(25 - wd2, 1, toDraw, WHITE);

	toDraw = "Inventory";
	wd2 = toDraw.length() / 2;
	SetStringAt(65 - wd2, 1, toDraw, WHITE);

	toDraw = "(Arrow Keys to navigate, Enter to select, Esc to Exit)";
	wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 23, toDraw, WHITE);

	toDraw = "Head: ";
	SetStringAt(10, 6, toDraw, WHITE);
	toDraw = "Body: ";
	SetStringAt(10, 8, toDraw, WHITE);
	toDraw = "Legs: ";
	SetStringAt(10, 10, toDraw, WHITE);
	toDraw = "Weapon: ";
	SetStringAt(8, 12, toDraw, WHITE);
	toDraw = "Implant: ";
	SetStringAt(7, 14, toDraw, WHITE);

	// Show inventory items
	Player* p = DataManager::Instance()->GetPlayer();
	Inventory inv = p->GetInventory();
	if(inv.NumItems() == 0) {
		int attr = WHITE;
		if(m_inInventoryArea) {
			attr = YELLOW_BOLD;
		}
		toDraw = "<empty>";
		SetStringAt(51, 3, toDraw, attr);
	}
	else {
		ItemList items = inv.GetItems();
		int counter = 0;
		for(ItemList::iterator i = items.begin(); i != items.end(); i++) {
			int attr = WHITE;
			if(m_inInventoryArea && counter == m_selectIdx) {
				attr = YELLOW_BOLD;
			}
			Item* toShow = *i;
			toDraw = toShow->GetDisplayName();
			SetStringAt(51, 3 + counter, toDraw, attr);
			counter++;
		}
	}

	// Show the equipped items
	DrawPaperDollItem(p->GetHeadItem(), 6, 0);
	DrawPaperDollItem(p->GetBodyItem(), 8, 1);
	DrawPaperDollItem(p->GetLegsItem(), 10, 2);
	DrawPaperDollItem(p->GetWeaponItem(), 12, 3);
	DrawPaperDollItem(p->GetImplantItem(), 14, 4);

	//stringstream s;
	//s << "num items " << inv.NumItems();
	//toDraw = s.str();
	//SetStringAt(1, 22, toDraw, WHITE);
}

void InventoryView::DrawPaperDollItem(Item* i, int y, int idx) {
	string toDraw;
	int attr = WHITE_BOLD;
	if(i) {
		toDraw = i->GetDisplayName();
	}
	else {
		toDraw = "<empty>";
	}
	if(!m_inInventoryArea && idx == m_selectIdx) {
		attr = YELLOW_BOLD;
	}
	SetStringAt(16, y, toDraw, attr);
}

void InventoryView::ResetState() {
	m_inInventoryArea = true;
	m_selectIdx = 0;
}
