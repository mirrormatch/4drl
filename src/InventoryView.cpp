
#include "InventoryView.h"
#include "GameState.h"
#include "Player.h"
#include "Inventory.h"
#include "DataManager.h"
#include "Item.h"
#include "ArmorItem.h"
#include "Weapon.h"
#include "Implant.h"
#include "Consumable.h"
#include <sstream>

InventoryView::InventoryView(GameState* gs, int w, int h) :
	View(gs, w, h), m_inInventoryArea(true), m_selectIdx(0), m_scrollY(0) {
}

InventoryView::~InventoryView() {
}

bool InventoryView::RequestInput() {
	int ch = getch();
	Player* p = DataManager::Instance()->GetPlayer();
	Inventory& inv = p->GetInventory();
	switch(ch) {
		case KEY_UP:
			if(m_inInventoryArea && inv.NumItems() == 0) {
				break;
			}
			m_selectIdx--;
			if(m_selectIdx < 0) {
				m_selectIdx = 0;
			}
		break;
		case KEY_DOWN:
			if(m_inInventoryArea && inv.NumItems() == 0) {
				break;
			}
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
		case 'd':
			if(m_inInventoryArea && m_selectIdx < inv.NumItems()) {
				inv.RemoveItemAtIndex(m_selectIdx);
				m_selectIdx = 0;
				m_scrollY = 0;
			}
			break;
		case KEY_LEFT:
			m_inInventoryArea = !m_inInventoryArea;
			m_selectIdx = 0;
		break;
		case KEY_RIGHT:
			m_inInventoryArea = !m_inInventoryArea;
			m_selectIdx = 0; break;
		case '\n':
		case KEY_ENTER:
			HandleItemSelection();
			break;
		case 'x':
			m_parent->ChangeState(GAME_STATE_MAIN);
			break;
	}
	if(m_inInventoryArea && !IsIndexOnScreen(m_selectIdx)) {
		if(m_selectIdx < m_scrollY) {
			m_scrollY = m_selectIdx;
		}
		else {
			m_scrollY = m_selectIdx - 18;
			if(m_scrollY < 0) {
				m_scrollY = 0;
			}
		}
	}
	return false;
}

bool InventoryView::IsIndexOnScreen(int idx) {
	return idx >= m_scrollY && idx < m_scrollY + 18;
}

void InventoryView::HandleItemSelection() {
	Player* p = DataManager::Instance()->GetPlayer();
	Inventory& inv = p->GetInventory();
	if(m_inInventoryArea) {
		if(inv.NumItems() > 0) {
			Item* toUse = inv.ItemAtIndex(m_selectIdx);
			Item* oldItem = NULL;
			if(!toUse->CanUse()) {
				stringstream s;
				s << toUse->GetDisplayName() << " requires level " << toUse->GetRequiredLevel();
				string toDisp = s.str();
				DataManager::Instance()->AppendStatusString(toDisp);
				return;
			}
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
				case E_CONSUMABLE:
					if(toUse->CanStack()) {
						Consumable* c = (Consumable*)toUse;
						c->ApplyEffect();
						if(toUse->GetStackSize() < 1) {
							inv.RemoveItem(toUse);
						}
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

	toDraw = "(Arrows navigate, Enter selects, 'd' discards, 'x' exits. List scrolls)";
	wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 23, toDraw, WHITE);

	toDraw = DataManager::Instance()->GetStatusString();
	DataManager::Instance()->ClearStatusString();
	if(toDraw != "()") {
		wd2 = toDraw.length() / 2;
		SetStringAt(1, 22, toDraw, YELLOW_BOLD);
	}

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
		int counter = m_scrollY;
		stringstream s;
		for(ItemList::iterator i = items.begin(); i != items.end(); i++) {
			if(counter < m_scrollY) {
				continue;
			}
			if(counter >= m_scrollY + 19) {
				break;
			}
			int attr = WHITE;
			if(m_inInventoryArea && counter == m_selectIdx) {
				attr = YELLOW_BOLD;
			}
			Item* toShow = *i;
			s.str("");
			s << (counter + 1) << ". " << toShow->GetDisplayName();
			if(toShow->CanStack()) {
				s << " (" << toShow->GetStackSize() << ")";
			}
			toDraw = s.str();
			if(toDraw.length() > 28) {
				toDraw.erase(28);
			}
			SetStringAt(51, 3 + counter - m_scrollY, toDraw, attr);
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
	//s << "scrolly: " << m_scrollY << " selectidx: " << m_selectIdx;
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
	m_scrollY = 0;
}
