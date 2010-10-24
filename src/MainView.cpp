
#include <ncurses.h>
#include <sstream>
#include "MainView.h"
#include "GameState.h"
#include "Level.h"
#include "Entity.h"
#include "DataManager.h"
#include "Player.h"

MainView::MainView(GameState* gs, int w, int h) : 
	View(gs, w, h), m_scrollX(0), m_scrollY(0) {
}

MainView::~MainView() {
}

void MainView::Initialize() {
	View::Initialize();
	Player* p = DataManager::Instance()->GetPlayer();
	m_scrollX = p->GetX() - 40;
	m_scrollY = p->GetY() - 10;
}

void MainView::RequestInput() {
	int ch = getch();
	Player* p = DataManager::Instance()->GetPlayer();
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		case KEY_LEFT:
			if(p->Advance(-1, 0)) {
				m_scrollX -= 1;
			}
			break;
		case KEY_RIGHT:
			if(p->Advance(1, 0)) {
				m_scrollX += 1;
			}
			break;
		case KEY_UP:
			if(p->Advance(0, -1)) {
				m_scrollY -= 1;
			}
			break;
		case KEY_DOWN:
			if(p->Advance(0, 1)) {
				m_scrollY += 1;
			}
			break;
		case 'n':
			DataManager::Instance()->GoToNextLevel();
			Player* p = DataManager::Instance()->GetPlayer();
			m_scrollX = p->GetX() - 40;
			m_scrollY = p->GetY() - 10;
			break;
	}
}

void MainView::Update() {
	Clear();
	Level* level = DataManager::Instance()->GetCurrentLevel();
	int lvlWidth = level->GetWidth();
	int lvlHeight = level->GetHeight();

	for(int x = m_scrollX; x < m_scrollX + 80; x++) {
		for(int y = m_scrollY; y <= m_scrollY + 20; y++) {
			if(x < 0 || y < 0 || x >= lvlWidth || y >= lvlHeight) {
				SetCharAt(x - m_scrollX, y - m_scrollY, '#', WHITE);
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
}

void MainView::DrawStats(Player* p) {

	for(int x = 0; x < 80; x++) {
		SetCharAt(x, 21, '-', WHITE_BOLD);
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
}

