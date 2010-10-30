
#include <sstream>
#include "MainView.h"
#include "GameState.h"
#include "Level.h"
#include "Entity.h"
#include "DataManager.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"

MainView::MainView(GameState* gs, int w, int h) : 
	View(gs, w, h), m_scrollX(0), m_scrollY(0), m_state(MVIS_MAIN) {
}

MainView::~MainView() {
}

void MainView::Initialize() {
	View::Initialize();
	Player* p = DataManager::Instance()->GetPlayer();
	m_scrollX = p->GetX() - 40;
	m_scrollY = p->GetY() - 10;
}

void MainView::ResetState() {
	Player* p = DataManager::Instance()->GetPlayer();
	m_scrollX = p->GetX() - 40;
	m_scrollY = p->GetY() - 10;
	m_state = MVIS_MAIN;
}

bool MainView::RequestInput() {
	int ch = getch();
	switch(m_state) {
		case MVIS_TARGET_SELECT:
			return HandleTargetSelectInput(ch);
		case MVIS_MAIN:
		default:
			return HandleMainInput(ch);
	}
}


bool MainView::HandleMainInput(int ch) {
	KeyType t = KeyConverter::Instance()->KeyForInput(ch);
	Player* p = DataManager::Instance()->GetPlayer();
	switch(t) {
		case K_QUIT:
			m_parent->RequestQuit();
			return false;
		case K_LEFT:
			if(p->Advance(-1, 0)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case K_RIGHT:
			if(p->Advance(1, 0)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case K_UP:
			if(p->Advance(0, -1)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case K_DOWN:
			if(p->Advance(0, 1)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case K_ATTACK:
			p->AttackTarget();
			break;
		case K_NEXT_TURN:
			// Do nothing, just skipping a turn
			break;
		case K_TARGET_MODE:
			// Change to targeting mode
			m_state = MVIS_TARGET_SELECT;
			SetCursorVisible(true);
			return false;
		case K_CLEAR:
			DataManager::Instance()->GetCurrentLevel()->ResetDebugFlags();
			return false;
		case K_INVENTORY:
			m_parent->ChangeState(GAME_STATE_INVENTORY);
			return false;
		case K_HELP:
			m_parent->ChangeState(GAME_STATE_HELP);
			return false;
		//case 'n':
		//	DataManager::Instance()->GoToNextLevel();
		//	Player* p = DataManager::Instance()->GetPlayer();
		//	m_scrollX = p->GetX() - 40;
		//	m_scrollY = p->GetY() - 10;
		//	break;
		default:
			return false;
	}
	return true;
}

bool MainView::HandleTargetSelectInput(int ch) {
	Player* p = DataManager::Instance()->GetPlayer();
	Level* l = DataManager::Instance()->GetCurrentLevel();
	KeyType t = KeyConverter::Instance()->KeyForInput(ch);
	int tx, ty;
	switch(t) {
		case K_EXIT:
			m_state = MVIS_MAIN;
			SetCursorVisible(false);
			break;
		case K_LEFT:
			SetCursorPosition(m_cursorX - 1, m_cursorY);
			break;
		case K_RIGHT:
			SetCursorPosition(m_cursorX + 1, m_cursorY);
			break;
		case K_UP:
			SetCursorPosition(m_cursorX, m_cursorY - 1);
			break;
		case K_DOWN:
			SetCursorPosition(m_cursorX, m_cursorY + 1);
			break;
		case K_SELECT:
			tx = m_scrollX + m_cursorX;
			ty = m_scrollY + m_cursorY;
			if(l->EntityAt(tx, ty) && l->EntityAt(tx, ty)->GetClass() == E_MONSTER) {
				Monster* m = (Monster*)l->EntityAt(tx, ty);
				p->SetTarget(m);
				string statusline = m->GetDisplayName() + " targetted.";
				DataManager::Instance()->AppendStatusString(statusline);
				m_state = MVIS_MAIN;
				SetCursorVisible(false);
			}
			break;
		case K_QUIT:
			m_parent->RequestQuit();
			break;
		default:
			break;
	}
	return false;
}

void MainView::Update() {
	Clear();
	Level* level = DataManager::Instance()->GetCurrentLevel();
	int lvlWidth = level->GetWidth();
	int lvlHeight = level->GetHeight();
	Player* p = DataManager::Instance()->GetPlayer();

	for(int x = m_scrollX; x < m_scrollX + 80; x++) {
		for(int y = m_scrollY; y <= m_scrollY + 19; y++) {
			if(x < 0 || y < 0 || x >= lvlWidth || y >= lvlHeight) {
				if(level->AnyAdjacentAreFloors(x, y) && level->AnyAdjacentAreVisible(x, y)) {
					SetCharAt(x - m_scrollX, y - m_scrollY, '#', WHITE);
				}
				else {
					SetCharAt(x - m_scrollX, y - m_scrollY, ' ', WHITE);
				}
				continue;
			}
			if(level->SquareAt(x, y)->hasBeenSeen == false) {
				SetCharAt(x - m_scrollX, y - m_scrollY, ' ');
				continue;
			}
			switch(level->SquareAt(x, y)->type) {
				case ST_VOID:
					if(level->SquareAt(x, y)->debugFlag) {
						SetCharAt(x - m_scrollX, y - m_scrollY, '?', RED_BOLD);
					}
					else {
						SetCharAt(x - m_scrollX, y - m_scrollY, ' ');
					}
					break;
				case ST_EMPTY:
					if(level->SquareAt(x, y)->debugFlag) {
						SetCharAt(x - m_scrollX, y - m_scrollY, '?', RED_BOLD);
					}
					else {
						int attr = WHITE;
						if(level->SquareAt(x, y)->inView) {
							attr = YELLOW;
						}
						SetCharAt(x - m_scrollX, y - m_scrollY, '.', attr);
					}
					break;
				case ST_TEST_COORIDOR:
					SetCharAt(x - m_scrollX, y - m_scrollY, '@', YELLOW_BOLD);
					break;
				case ST_WALL:
					if(level->SquareAt(x, y)->debugFlag) {
						SetCharAt(x - m_scrollX, y - m_scrollY, '?', RED_BOLD);
					}
					else {
						SetCharAt(x - m_scrollX, y - m_scrollY, '#', WHITE);
					}
					break;
			}

			Entity* e = level->EntityAt(x, y);
			if(e) {
				if(level->SquareAt(x, y)->inView) {
					if(e->GetClass() == E_MONSTER) {
						Monster* m = (Monster*)e;
						int attr = WHITE_BOLD;
						int lvldiff = m->GetLevel() - p->GetLevel();
						if(p->GetTarget() == m) {
							attr = MAGENTA_BOLD;
						}
						else if(lvldiff < -1) {
							attr = WHITE_BOLD;
						}
						else if(lvldiff < 0) {
							attr = BLUE_BOLD;
						}
						else if(lvldiff  < 1) {
							attr = GREEN_BOLD;
						}
						else if(lvldiff < 2) {
							attr = YELLOW_BOLD;
						}
						else {
							attr = RED_BOLD;
						}
						SetCharAt(x - m_scrollX, y - m_scrollY, 
								e->GetDisplayChar(), attr);
					}
					else {
						SetCharAt(x - m_scrollX, y - m_scrollY, 
								e->GetDisplayChar(), e->GetDisplayFlags());
					}
				}
				else if(level->SquareAt(x, y)->hasBeenSeen && e->GetClass() != E_MONSTER) {
					SetCharAt(x - m_scrollX, y - m_scrollY, 
							e->GetDisplayChar(), e->GetDisplayFlags());
				}
			}
		}
	}

	SetCharAt(p->GetX() - m_scrollX, p->GetY() - m_scrollY, p->GetDisplayChar(),
		p->GetDisplayFlags());

	DrawStats(p);
	if(m_state == MVIS_MAIN) {
		SetCursorPosition(p->GetX() - m_scrollX, p->GetY() - m_scrollY);
	}
}

void MainView::DrawStats(Player* p) {

	for(int x = 0; x < 80; x++) {
		SetCharAt(x, 20, '-', WHITE_BOLD);
	}

	Level* level = DataManager::Instance()->GetCurrentLevel();
	stringstream s;
	s << "Zone: " << level->GetLevelNumber();
	s << "  STR: " << p->GetSTR();
	s << "  DEX: " << p->GetDEX();
	s << "  ACC: " << p->GetACC();
	s << "  AC: " << p->GetAC();
	s << "  W: ";
	if(p->GetWeaponItem()) {
		s << p->GetWeaponItem()->GetDisplayName();
	}
	else {
		s << "<empty>";
	}
	string str = s.str();
	SetStringAt(0, 23, str, WHITE_BOLD);

	s.str("");
	s << p->GetFullName();
	s << "  Level: " << p->GetLevel();
	s << "  XP: " << p->GetXP();
	s << "  HP: " << p->GetCurrentHP() << "/" << p->GetHP();
	str = s.str();
	SetStringAt(0, 22, str, WHITE_BOLD);

	string statusLine = DataManager::Instance()->GetStatusString();
	if(statusLine != "()") {
		int wd2 = statusLine.length() / 2;
		SetStringAt(40 - wd2, 21, statusLine, YELLOW_BOLD);
		DataManager::Instance()->ClearStatusString();
	}
	else if(m_state == MVIS_TARGET_SELECT) {
		str = "(Move cursor to target and hit Enter, 'x' to exit with no target)";
		int wd2 = str.length() / 2;
		SetStringAt(40 - wd2, 21, str, YELLOW_BOLD);
	}

	str = "'?' for help";
	SetStringAt(80 - str.length(), 23, str, WHITE);

}

