
#include "Player.h"
#include "DataManager.h"
#include "Level.h"
#include "Item.h"
#include "Helm.h"
#include "BodyArmor.h"
#include "Pants.h"
#include "Weapon.h"
#include "Implant.h"

Player::Player() : 
	Entity('@', YELLOW_BOLD, E_PLAYER), m_headSlot(NULL), m_bodySlot(NULL), m_legsSlot(NULL), m_weaponSlot(NULL), m_implantSlot(NULL) {
}

Player::~Player() {
}

void Player::Update() {
}

void Player::Activate() {
}

bool Player::Advance(int xinc, int yinc) {
	Level* l = DataManager::Instance()->GetCurrentLevel();
	if(l->IsSquareOpen(m_x + xinc, m_y + yinc)) {
		SetPosition(m_x + xinc, m_y + yinc);
		Entity* e = l->EntityAt(m_x, m_y);
		if(e) {
			e->Activate();
		}
		return true;
	}

	return false;
}

void Player::CreateDefaults() {
	SetName("Biff");
	SetTitle("Space Librarian");
	SetXP(0);
	SetLevel(1);
	SetHP(40);
	SetCurrentHP(40);
	SetSTR(10);
	SetDEX(10);
	SetACC(10);
	SetAC(10);
}

string& Player::GetName() {
	return m_name;
}

void Player::SetName(string name) {
	m_name = name;
}

string& Player::GetTitle() {
	return m_title;
}

void Player::SetTitle(string title) {
	m_title = title;
}

string& Player::GetFullName() {
	// FIXME: should only calculate this when name or title change
	m_fullName = m_name + " the " + m_title;
	return m_fullName;
}

int Player::GetXP() {
	return m_xp;
}

void Player::SetXP(int xp) {
	m_xp = xp;
}

void Player::IncrementXP(int inc) {
	m_xp += inc;
}

int Player::GetLevel() {
	return m_level;
}

void Player::SetLevel(int lvl) {
	m_level = lvl;
}

void Player::IncrementLevel(int inc) {
	m_level += inc;
}

int Player::GetHP() {
	return m_hp;
}

void Player::SetHP(int hp) {
	m_hp = hp;
}

void Player::IncrementHP(int inc) {
	m_hp += inc;
}

int Player::GetCurrentHP() {
	return m_currentHP;
}

void Player::SetCurrentHP(int chp) {
	m_currentHP = chp;
}

void Player::IncrementCurrentHP(int inc) {
	m_currentHP += inc;
}

int Player::GetSTR() {
	return m_str;
}

void Player::SetSTR(int str) {
	m_str = str;
}

int Player::GetDEX() {
	return m_dex;
}

void Player::SetDEX(int dex) {
	m_dex = dex;
}

int Player::GetACC() {
	return m_acc;
}

void Player::SetACC(int acc) {
	m_acc = acc;
}

int Player::GetAC() {
	return m_ac;
}

void Player::SetAC(int ac) {
	m_ac = ac;
}

Inventory& Player::GetInventory() {
	return m_inventory;
}

ArmorItem* Player::GetHeadItem() {
	return m_headSlot;
}

ArmorItem* Player::GetBodyItem() {
	return m_bodySlot;
}

ArmorItem* Player::GetLegsItem() {
	return m_legsSlot;
}

Weapon* Player::GetWeaponItem() {
	return m_weaponSlot;
}

Implant* Player::GetImplantItem() {
	return m_implantSlot;
}

void Player::SetHeadItem(ArmorItem* newItem) {
	if(m_headSlot) {
		m_ac -= m_headSlot->GetAC();
	}
	m_headSlot = newItem;
	m_ac += newItem->GetAC();
}

void Player::SetBodyItem(ArmorItem* newItem) {
	if(m_bodySlot) {
		m_ac -= m_bodySlot->GetAC();
	}
	m_bodySlot = newItem;
	m_ac += newItem->GetAC();
}

void Player::SetLegsItem(ArmorItem* newItem) {
	if(m_legsSlot) {
		m_ac -= m_legsSlot->GetAC();
	}
	m_legsSlot = newItem;
	m_ac += newItem->GetAC();
}

void Player::SetWeaponItem(Weapon* newItem) {
	m_weaponSlot = newItem;
}

void Player::SetImplantItem(Implant* newItem) {
	m_implantSlot = newItem;
}

void Player::ReturnHeadItemToInventory() {
	if(m_headSlot) {
		m_inventory.AddItem(m_headSlot);
		m_ac -= m_headSlot->GetAC();
		m_headSlot = NULL;
	}
}

void Player::ReturnBodyItemToInventory() {
	if(m_bodySlot) {
		m_inventory.AddItem(m_bodySlot);
		m_ac -= m_bodySlot->GetAC();
		m_bodySlot = NULL;
	}
}

void Player::ReturnLegsItemToInventory() {
	if(m_legsSlot) {
		m_inventory.AddItem(m_legsSlot);
		m_ac -= m_legsSlot->GetAC();
		m_legsSlot = NULL;
	}
}

void Player::ReturnWeaponItemToInventory() {
	if(m_weaponSlot) {
		m_inventory.AddItem(m_weaponSlot);
		m_weaponSlot = NULL;
	}
}

void Player::ReturnImplantItemToInventory() {
	if(m_implantSlot) {
		m_inventory.AddItem(m_implantSlot);
		m_implantSlot = NULL;
	}
}

