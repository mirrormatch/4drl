
#include <ncurses.h>
#include <sstream>
#include "MainView.h"
#include "GameState.h"
#include "Level.h"
#include "Entity.h"
#include "DataManager.h"

MainView::MainView(GameState* gs, int w, int h) : 
	View(gs, w, h), m_scrollX(0), m_scrollY(0) {
}

MainView::~MainView() {
}

void MainView::Initialize() {
	View::Initialize();
}

void MainView::RequestInput() {
	int ch = getch();
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		case KEY_LEFT:
			m_scrollX -= 1;
			break;
		case KEY_RIGHT:
			m_scrollX += 1;
			break;
		case KEY_UP:
			m_scrollY -= 1;
			break;
		case KEY_DOWN:
			m_scrollY += 1;
			break;
		case 'n':
			DataManager::Instance()->GoToNextLevel();
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

			if(level->EntityAt(x, y)) {
				SetCharAt(x - m_scrollX, y - m_scrollY, 
						level->EntityAt(x, y)->GetDisplayChar(), WHITE);
			}
		}
	}

	for(int x = 0; x < 80; x++) {
		SetCharAt(x, 21, '-', WHITE_BOLD);
	}
}

