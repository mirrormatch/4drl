
#include "DeathView.h"
#include "GameState.h"
#include "DataManager.h"

DeathView::DeathView(GameState* gs, int w, int h) : View(gs, w, h) {
}

DeathView::~DeathView() {
}

void DeathView::Initialize() {
	View::Initialize();
}

bool DeathView::RequestInput() {
	int ch = getch();
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		default:
			DataManager::Instance()->ResetAllData();
			m_parent->ChangeState(GAME_STATE_INTRO);
			break;
	}

	return false;
}

void DeathView::Update() {
	string s = "You have died. Sorry about that.";
	int wd2 = s.length() / 2;
	SetStringAt(40 - wd2, 10, s, WHITE);
	s = "(Press 'q' to quit, or any other key to start over)";
	wd2 = s.length() / 2;
	SetStringAt(40 - wd2, 12, s, YELLOW_BOLD);
}

void DeathView::ResetState() {
}

