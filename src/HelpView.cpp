
#include "HelpView.h"
#include "GameState.h"

HelpView::HelpView(GameState* gs, int w, int h) : View(gs, w, h) {
}

HelpView::~HelpView() {
}

void HelpView::Initialize() {
	View::Initialize();
}

bool HelpView::RequestInput() {
	KeyType t = KeyConverter::Instance()->KeyForInput(getch());
	switch(t) {
		case K_EXIT:
			m_parent->ChangeState(GAME_STATE_MAIN);
			break;
		default:
			break;
	}
	return false;
}

void HelpView::Update() {
	Clear();
	string todraw = "Help & Legend";
	int wd2 = todraw.length() / 2;
	SetStringAt(40 - wd2, 1, todraw, YELLOW_BOLD);

	todraw = "('x' to exit this screen)";
	wd2 = todraw.length() / 2;
	SetStringAt(40 - wd2, 23, todraw, YELLOW_BOLD);

	todraw = "Keys";
	SetStringAt(4, 4, todraw, WHITE_BOLD);
	todraw = "Arrow Keys - Move Around";
	SetStringAt(4, 6, todraw, WHITE_BOLD);
	todraw = "t - Select Target";
	SetStringAt(4, 8, todraw, WHITE_BOLD);
	todraw = "a - Attack";
	SetStringAt(4, 10, todraw, WHITE_BOLD);
	todraw = "i - Open Inventory";
	SetStringAt(4, 12, todraw, WHITE_BOLD);
	todraw = "x - Close Info Screens";
	SetStringAt(4, 14, todraw, WHITE_BOLD);
	todraw = "q - Quit Game";
	SetStringAt(4, 16, todraw, WHITE_BOLD);

	todraw = "Legend";
	SetStringAt(40, 4, todraw, WHITE_BOLD);
	SetCharAt(40, 6, '^', GREEN_BOLD);
	todraw = " - Stairs up";
	SetStringAt(41, 6, todraw, WHITE_BOLD);

	SetCharAt(40, 8, 'v', GREEN_BOLD);
	todraw = " - Stairs down";
	SetStringAt(41, 8, todraw, WHITE_BOLD);

	SetCharAt(40, 10, 'i', CYAN_BOLD);
	todraw = " - Item. Walk over to pick up.";
	SetStringAt(41, 10, todraw, WHITE_BOLD);

	SetCharAt(40, 12, 'M', RED_BOLD);
	todraw = " - Xoich. Short range, lots of HP";
	SetStringAt(41, 12, todraw, WHITE_BOLD);

	SetCharAt(40, 14, 'R', RED_BOLD);
	todraw = " - Reaper. Long range, low HP";
	SetStringAt(41, 14, todraw, WHITE_BOLD);
	
	SetCharAt(40, 16, 'M', WHITE_BOLD);
	SetCharAt(42, 16, 'M', BLUE_BOLD);
	SetCharAt(44, 16, 'M', GREEN_BOLD);
	SetCharAt(46, 16, 'M', YELLOW_BOLD);
	SetCharAt(48, 16, 'M', RED_BOLD);
	todraw = " - Color signifies difficulty";
	SetStringAt(49, 16, todraw, WHITE_BOLD);

}

