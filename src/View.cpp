
#include "View.h"
#include "GameState.h"

View::View(GameState* parent, int w, int h) : 
	m_parent(parent), m_width(w), m_height(h), m_screenData(NULL), m_screenAttrs(NULL), start(' '), m_cursorX(w-1), m_cursorY(h-1), m_visibleCursor(false) {
	curs_set(0);
}

void View::Initialize() {
	m_screenData = new char*[m_width];
	m_screenAttrs = new unsigned int*[m_width];
	for(int x = 0; x < m_width; x++) {
		m_screenData[x] = new char[m_height];
		m_screenAttrs[x] = new unsigned int[m_height];
		memset(m_screenData[x], ' ', m_height);
		memset(m_screenAttrs[x], 0, m_height * sizeof(unsigned int));
	}
}

View::~View() {
	if(m_screenData) {
		for(int x = 0; x < m_width; x++) {
			delete [] m_screenData[x];
		}
		delete [] m_screenData;
		m_screenData = NULL;
	}
	
	if(m_screenAttrs) {
		for(int x = 0; x < m_width; x++) {
			delete [] m_screenAttrs[x];
		}
		delete [] m_screenAttrs;
		m_screenAttrs = NULL;
	}
}
bool View::RequestInput() {
	char ch = getch();
	//TODO: remove this once we have real game screens, for now just so we reset
	// term
	string testString = "This is a test.";
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		case 'n':
			start++;
			ClearWith(start);
			break;
		case 't':
			SetStringAt(10, 10, testString, RED_BOLD);
			break;
		case 'p':
			start--;
			ClearWith(start);
			break;
	}

	return false;
}

void View::Update() {
	//default class doesn't do anything
}

void View::Draw() {
	erase(); // clear the curses screen
	// draw our stuff
	for(int y = 0; y < m_height; y++) {
		for(int x = 0; x < m_width; x++) {
			addch(m_screenData[x][y] | m_screenAttrs[x][y]);
		}
	}
	move(m_cursorY, m_cursorX);
}

void View::SetCharAt(int x, int y, char value, int flags) {
	m_screenData[x][y] = value;
	m_screenAttrs[x][y] = flags;
}

void View::SetStringAt(int x, int y, string& value, int flags) {
	for(unsigned int i = 0; i < value.length(); i++) {
		char c = value[i];
		m_screenData[x+i][y] = c | flags;
		m_screenAttrs[x+i][y] = flags;
	}
}

void View::Clear() {
	ClearWith(' ');
}

void View::ClearWith(char ch, int flags) {
	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			m_screenData[x][y] = ch;
			m_screenAttrs[x][y] = flags;
		}
	}
}

void View::ResetState() {
}

void View::SetCursorPosition(int x, int y) {
	m_cursorX = x;
	m_cursorY = y;
}

void View::SetCursorVisible(bool isVisible) {
	m_visibleCursor = isVisible;
	if(isVisible) {
		curs_set(1);
	}
	else {
		curs_set(0);
	}
}
