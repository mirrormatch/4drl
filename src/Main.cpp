#include <ncurses.h>
#include "GameState.h"
#include "GeneralIncludes.h"

void InitCurses() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	refresh();
	ColorPairs::InitializePairs();
}

void EndCurses() {
	endwin();
}

int main(int argc, char** argv) {
	InitCurses();

	//FIXME: for now assume it's a seed, need to go back and make flags
	int seed = 0;
	if(argc == 2) {
		seed = atoi(argv[1]);
	}
	GameState* gs = new GameState(seed);
	gs->Initialize();
	while(gs->IsRunning()) {
		gs->Update();
	}
	delete gs;

	EndCurses();

	return 0;
}
