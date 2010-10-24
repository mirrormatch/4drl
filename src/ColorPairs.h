
#ifndef _COLOR_PAIRS_H_
#define _COLOR_PAIRS_H_

#include <ncurses.h>

enum PairNames {
	WHITE_ON_BLACK = 1,
	RED_ON_BLACK = 2,
	YELLOW_ON_BLACK = 3,
	GREEN_ON_BLACK = 4,
	BLUE_ON_BLACK = 5,
	CYAN_ON_BLACK = 6,
	MAGENTA_ON_BLACK = 7
};

#define WHITE (COLOR_PAIR(WHITE_ON_BLACK))
#define WHITE_BOLD (A_BOLD | COLOR_PAIR(WHITE_ON_BLACK))

#define RED (COLOR_PAIR(RED_ON_BLACK))
#define RED_BOLD (A_BOLD | COLOR_PAIR(RED_ON_BLACK))

#define YELLOW (COLOR_PAIR(YELLOW_ON_BLACK))
#define YELLOW_BOLD (A_BOLD | COLOR_PAIR(YELLOW_ON_BLACK))

#define GREEN (COLOR_PAIR(GREEN_ON_BLACK))
#define GREEN_BOLD (A_BOLD | COLOR_PAIR(GREEN_ON_BLACK))

#define BLUE (COLOR_PAIR(BLUE_ON_BLACK))
#define BLUE_BOLD (A_BOLD | COLOR_PAIR(BLUE_ON_BLACK))

#define CYAN (COLOR_PAIR(CYAN_ON_BLACK))
#define CYAN_BOLD (A_BOLD | COLOR_PAIR(CYAN_ON_BLACK))

#define MAGENTA (COLOR_PAIR(MAGENTA_ON_BLACK))
#define CYAN_MAGENTA (A_BOLD | COLOR_PAIR(MAGENTA_ON_BLACK))

class ColorPairs {
public:
	static void InitializePairs();
};

#endif
