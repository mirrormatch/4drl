
#include <ncurses.h>
#include "MainView.h"
#include "GameState.h"
#include "Level.h"

MainView::MainView(GameState* gs, int w, int h) : View(gs, w, h) {
}

MainView::~MainView() {
}

void MainView::Initialize() {
	View::Initialize();
	m_level = new Level();
	m_level->Generate(80, 24, 10);
}

void MainView::RequestInput() {
	char ch = getch();
	//TODO: remove this once we have real game screens, for now just so we reset
	// term
	string testString = "This is a test.";
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		case 'n':
			delete m_level;
			m_level = new Level();
			m_level->Generate(80, 24, 10);
	}
}

void MainView::Update() {
	for(int x = 0; x < 80; x++) {
		for(int y = 0; y < 24; y++) {
			switch(m_level->SquareAt(x, y)->type) {
				case ST_VOID:
					SetCharAt(x, y, ' ');
					break;
				case ST_EMPTY:
					SetCharAt(x, y, '.');
					break;
			}
		}
	}
}

