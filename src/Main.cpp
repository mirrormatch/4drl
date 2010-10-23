#include <ncurses.h>
#include "GameState.h"

void InitCurses() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	refresh();
}

void EndCurses() {
	endwin();
}

int main(int argc, char** argv) {

	InitCurses();

	GameState* gs = new GameState();
	gs->Initialize();
	while(gs->IsRunning()) {
		gs->Update();
	}
	delete gs;

	EndCurses();

	return 0;
}
