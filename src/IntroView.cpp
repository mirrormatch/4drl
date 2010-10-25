
#include "IntroView.h"
#include "GameState.h"

IntroView::IntroView(GameState* gs, int w, int h) :
	View(gs, w, h) {
}

IntroView::~IntroView() {
}

void IntroView::Initialize() {
	View::Initialize();
}

bool IntroView::RequestInput() {
	int ch = getch();
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		default:
			m_parent->ChangeState(GAME_STATE_PLAYER_CREATE);
			break;
	}

	return false;
}

void IntroView::Update() {
	Clear();
	string toDraw = ". . . t r a n s m i s s i o n . . .";
	int wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 11, toDraw, YELLOW_BOLD);
	toDraw = "(press any key to continue)";
	wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 13, toDraw, WHITE);
}

