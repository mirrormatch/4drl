
#include <ncurses.h>
#include "MainView.h"
#include "GameState.h"
#include "Level.h"

MainView::MainView(GameState* gs, int w, int h) : 
	View(gs, w, h), m_scrollX(0), m_scrollY(0) {
}

MainView::~MainView() {
}

void MainView::Initialize() {
	View::Initialize();
	m_level = new Level();
	m_level->Generate(160, 48, 40);
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
			delete m_level;
			m_level = new Level();
			m_level->Generate(160, 48, 40);
	}
}

void MainView::Update() {
	int lvlWidth = m_level->GetWidth();
	int lvlHeight = m_level->GetHeight();

	for(int x = m_scrollX; x < m_scrollX + 80; x++) {
		for(int y = m_scrollY; y <= m_scrollY + 20; y++) {
			if(x < 0 || y < 0 || x >= lvlWidth || y >= lvlHeight) {
				SetCharAt(x - m_scrollX, y - m_scrollY, '#');
				continue;
			}
			switch(m_level->SquareAt(x, y)->type) {
				case ST_VOID:
					SetCharAt(x - m_scrollX, y - m_scrollY, ' ');
					break;
				case ST_EMPTY:
					SetCharAt(x - m_scrollX, y - m_scrollY, '.', GREEN);
					break;
			}
		}
		SetCharAt(x - m_scrollX, 21, '-');
	}
}

