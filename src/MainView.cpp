
#include <ncurses.h>
#include <sstream>
#include "MainView.h"
#include "GameState.h"
#include "Level.h"
#include "Entity.h"
#include "DataManager.h"
#include "Player.h"
#include "Monster.h"

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
	Player* p = DataManager::Instance()->GetPlayer();
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			return false;
		case KEY_LEFT:
			if(p->Advance(-1, 0)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case KEY_RIGHT:
			if(p->Advance(1, 0)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case KEY_UP:
			if(p->Advance(0, -1)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case KEY_DOWN:
			if(p->Advance(0, 1)) {
				m_scrollX = p->GetX() - 40;
				m_scrollY = p->GetY() - 10;
			}
			break;
		case 'a':
			p->AttackTarget();
			break;
		case ' ':
			// Do nothing, just skipping a turn
			break;
		case 't':
			// Change to targeting mode
			m_state = MVIS_TARGET_SELECT;
			SetCursorVisible(true);
			return false;
		case 'i':
			m_parent->ChangeState(GAME_STATE_INVENTORY);
			return false;
		//case 'n':
		//	DataManager::Instance()->GoToNextLevel();
		//	Player* p = DataManager::Instance()->GetPlayer();
		//	m_scrollX = p->GetX() - 40;
		//	m_scrollY = p->GetY() - 10;
		//	break;
	}
	return true;
}

bool MainView::HandleTargetSelectInput(int ch) {
	Player* p = DataManager::Instance()->GetPlayer();
	Level* l = DataManager::Instance()->GetCurrentLevel();
	int tx, ty;
	switch(ch) {
		case 27:
			m_state = MVIS_MAIN;
			SetCursorVisible(false);
			break;
		case KEY_LEFT:
			SetCursorPosition(m_cursorX - 1, m_cursorY);
			break;
		case KEY_RIGHT:
			SetCursorPosition(m_cursorX + 1, m_cursorY);
			break;
		case KEY_UP:
			SetCursorPosition(m_cursorX, m_cursorY - 1);
			break;
		case KEY_DOWN:
			SetCursorPosition(m_cursorX, m_cursorY + 1);
			break;
		case KEY_ENTER:
		case '\n':
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
		case 'q':
			m_parent->RequestQuit();
			break;
	}
	return false;
}

void MainView::Update() {
	Clear();
	Level* level = DataManager::Instance()->GetCurrentLevel();
	int lvlWidth = level->GetWidth();
	int lvlHeight = level->GetHeight();

	for(int x = m_scrollX; x < m_scrollX + 80; x++) {
		for(int y = m_scrollY; y <= m_scrollY + 19; y++) {
			if(x < 0 || y < 0 || x >= lvlWidth || y >= lvlHeight) {
				SetCharAt(x - m_scrollX, y - m_scrollY, ' ', WHITE);
				continue;
			}
			switch(level->SquareAt(x, y)->type) {
				case ST_VOID:
					SetCharAt(x - m_scrollX, y - m_scrollY, ' ');
					break;
				case ST_EMPTY:
					SetCharAt(x - m_scrollX, y - m_scrollY, '.', WHITE);
					break;
				case ST_TEST_COORIDOR:
					SetCharAt(x - m_scrollX, y - m_scrollY, '@', YELLOW_BOLD);
					break;
				case ST_WALL:
					SetCharAt(x - m_scrollX, y - m_scrollY, '#', WHITE);
					break;
			}

			Entity* e = level->EntityAt(x, y);
			if(e) {
				SetCharAt(x - m_scrollX, y - m_scrollY, 
						e->GetDisplayChar(), e->GetDisplayFlags());
			}
		}
	}

	Player* p = DataManager::Instance()->GetPlayer();
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
		str = "(Place the cursor over your desired target and hit Enter)";
		int wd2 = str.length() / 2;
		SetStringAt(40 - wd2, 21, str, YELLOW_BOLD);
	}
}

