
#include "Player.h"
#include "DataManager.h"
#include "Level.h"

Player::Player() : Entity('@', YELLOW_BOLD) {
}

Player::~Player() {
}

void Player::Update() {
}

bool Player::Advance(int xinc, int yinc) {
	Level* l = DataManager::Instance()->GetCurrentLevel();
	if(l->IsSquareOpen(m_x + xinc, m_y + yinc)) {
		SetPosition(m_x + xinc, m_y + yinc);
		//FIXME: interact with items on the board
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

