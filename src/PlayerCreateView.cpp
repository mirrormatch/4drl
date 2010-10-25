
#include "PlayerCreateView.h"
#include "DataManager.h"
#include "GameState.h"
#include "Player.h"

PlayerCreateView::PlayerCreateView(GameState* gs, int w, int h) :
	View(gs, w, h) {
}

PlayerCreateView::~PlayerCreateView() {
}

void PlayerCreateView::Initialize() {
	View::Initialize();
	m_name = "";
	m_selectIdx = 0;
}

void PlayerCreateView::RequestInput() {
	int ch = getch();
	switch(m_state) {
		case PC_NAME:
			HandleNameInput(ch);
		break;
		case PC_CLASS:
			HandleClassInput(ch);
		break;
	}
}

void PlayerCreateView::HandleNameInput(int ch) {
	switch(ch) {
	case KEY_BACKSPACE:
		if(m_name.length() > 0) {
			m_name.erase(m_name.length() - 1);
		}
		break;
	case KEY_ENTER:
	case '\n':
		if(m_name.length() > 0) {
			DataManager::Instance()->GetPlayer()->SetName(m_name);
			m_state = PC_CLASS;
		}
		break;
	case '\t':
	case ' ':
		// throwaway whitespaces
		break;
	default:
		m_name.append(1, (char)ch);
		break;
	}
}

void PlayerCreateView::HandleClassInput(int ch) {
	switch(ch) {
		case KEY_UP:
			m_selectIdx--;
			if(m_selectIdx < 0) {
				m_selectIdx = 0;
			}
			break;
		case KEY_DOWN:
			m_selectIdx++;
			if(m_selectIdx >= DataManager::Instance()->GetClassNames().size()) {
				m_selectIdx = DataManager::Instance()->GetClassNames().size() - 1;
			}
			break;
		case KEY_ENTER:
		case '\n':
			DataManager::Instance()->GetPlayer()->SetTitle(
				DataManager::Instance()->GetClassNames()[m_selectIdx]);
			m_parent->ChangeState(GAME_STATE_MAIN);
			break;
	}
}

void PlayerCreateView::Update() {
	Clear();
	switch(m_state) {
		case PC_NAME:
			DrawNameScreen();
			break;
		case PC_CLASS:
			DrawClassScreen();
			break;
	}
}

void PlayerCreateView::DrawNameScreen() {
	string toDraw = "Player, what is your name?";
	int wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 11, toDraw, WHITE_BOLD);
	if(m_name.length() > 0) {
		wd2 = m_name.length() / 2;
		SetStringAt(40 - wd2, 12, m_name, YELLOW_BOLD);
	}

	toDraw = "(type your chosen name and then press return)";
	wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 23, toDraw, WHITE);
}

void PlayerCreateView::DrawClassScreen() {
	string toDraw = m_name + ", what is your class?";
	int wd2 = toDraw.length() / 2;
	SetStringAt(40 - wd2, 10, toDraw, WHITE_BOLD);
	const StringVector classes = DataManager::Instance()->GetClassNames();
	for(unsigned int i = 0; i < classes.size(); i++) {
		int attr = WHITE;
		if(i == m_selectIdx) {
			attr = YELLOW_BOLD;
		}
		toDraw = classes[i];
		wd2 = toDraw.length() / 2;
		SetStringAt(40 - wd2, 12 + i, toDraw, attr);
	}
}
