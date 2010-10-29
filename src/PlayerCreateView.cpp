
#include "PlayerCreateView.h"
#include "DataManager.h"
#include "GameState.h"
#include "Player.h"
#include <sstream>

PlayerCreateView::PlayerCreateView(GameState* gs, int w, int h) :
	View(gs, w, h), m_state(PC_NAME) {
}

PlayerCreateView::~PlayerCreateView() {
}

void PlayerCreateView::Initialize() {
	View::Initialize();
	m_name = "";
	m_selectIdx = 0;
}

void PlayerCreateView::ResetState() {
	m_name = "";
	m_selectIdx = 0;
	m_state = PC_NAME;
}

bool PlayerCreateView::RequestInput() {
	int ch = getch();
	switch(m_state) {
		case PC_NAME:
			HandleNameInput(ch);
		break;
		case PC_CLASS:
			HandleClassInput(ch);
		break;
	}

	return false;
}

void PlayerCreateView::HandleNameInput(int ch) {
	KeyType t = KeyConverter::Instance()->KeyForInput(ch);
	switch(t) {
	case K_BACKSPACE:
		if(m_name.length() > 0) {
			m_name.erase(m_name.length() - 1);
		}
		break;
	case K_SELECT:
		if(m_name.length() > 0) {
			DataManager::Instance()->GetPlayer()->SetName(m_name);
			m_state = PC_CLASS;
		}
		break;
	default:
		if(ch <= ' ') {
			// no whitespace or control codes, please
			break;
		}
		m_name.append(1, (char)ch);
		break;
	}
}

void PlayerCreateView::HandleClassInput(int ch) {
	KeyType t = KeyConverter::Instance()->KeyForInput(ch);
	switch(t) {
		case K_UP:
			if(m_selectIdx > 0) {
				m_selectIdx--;
			}
			break;
		case K_DOWN:
			m_selectIdx++;
			if(m_selectIdx >= DataManager::Instance()->GetClassNames().size()) {
				m_selectIdx = DataManager::Instance()->GetClassNames().size() - 1;
			}
			break;
		case K_SELECT:
			DataManager::Instance()->GetPlayer()->SetTitle(
				DataManager::Instance()->GetClassNames()[m_selectIdx]);
			m_parent->ChangeState(GAME_STATE_MAIN);
			break;
		default:
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

/*
	stringstream s;
	s << "select idx: " << m_selectIdx;
	toDraw = s.str();
	SetStringAt(1, 20, toDraw, WHITE);
*/
}
