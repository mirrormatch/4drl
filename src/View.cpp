
#include <ncurses.h>
#include "View.h"
#include "GameState.h"

View::View(GameState* parent, int w, int h) : 
	m_parent(parent), m_width(w), m_height(h), m_screenData(NULL), start(33) {
}

void View::Initialize() {
	m_screenData = new char*[m_width];
	for(int x = 0; x < m_width; x++) {
		m_screenData[x] = new char[m_height];
		memset(m_screenData[x], 33, m_height);
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
}

void View::RequestInput() {
	char ch = getch();
	//TODO: remove this once we have real game screens, for now just so we reset
	// term
	switch(ch) {
		case 'q':
			m_parent->RequestQuit();
			break;
		case 'n':
			start++;
			ClearWith(start);
			break;
		case 'p':
			start--;
			ClearWith(start);
			break;
	}
}

void View::Update() {
	//default class doesn't do anything
}

void View::Draw() {
	clear(); // clear the curses screen
	// draw our stuff
	for(int y = 0; y < m_height; y++) {
		for(int x = 0; x < m_width; x++) {
			addch(m_screenData[x][y]);
		}
	}
}

void View::SetCharAt(int x, int y, char value, int flags) {
	m_screenData[x][y] = value | flags;
}

void View::SetStringAt(int x, int y, string& value, int flags) {
	for(unsigned int i = 0; i < value.length(); i++) {
		char c = value[i];
		m_screenData[x][y] = c | flags;
	}
}

void View::Clear() {
	ClearWith(' ');
}

void View::ClearWith(char ch, int flags) {
	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			m_screenData[x][y] = ch | flags;
		}
	}
}
