

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "GeneralIncludes.h"

class Room {
public:
	Room(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {
	}

	virtual ~Room() {}

	bool Overlaps(Room* r1) {
		int x1 = x; int x2 = x + width;
		int y1 = y; int y2 = y + height;
		int r1x1 = r1->x; int r1x2 = r1->x + width;
		int r1y1 = r1->y; int r1y2 = r1->y + height;

		// Check to see if any of the points of r1 overlap this room
		if(r1x1 >= x1 && r1x1 <= x2 && r1y1 >= y1 && r1y1 <= y2) {
			return true;
		}
		else if(r1x2 >= x1 && r1x2 <= x2 && r1y1 >= y1 && r1y1 <= y2) {
			return true;
		}
		else if(r1x2 >= x1 && r1x2 <= x2 && r1y2 >= y1 && r1y2 <= y2) {
			return true;
		}
		else if(r1x1 >= x1 && r1x1 <= x2 && r1y2 >= y1 && r1y2 <= y2) {
			return true;
		}

		// Now checking the other way -- in case this room is contained in r1
		if(x1 >= r1x1 && x1 <= r1x2 && y1 >= r1y1 && y1 <= r1y2) {
			return true;
		}
		else if(x2 >= r1x1 && x2 <= r1x2 && y1 >= r1y1 && y1 <= r1y2) {
			return true;
		}
		else if(x2 >= r1x1 && x2 <= r1x2 && y2 >= r1y1 && y2 <= r1y2) {
			return true;
		}
		else if(x1 >= r1x1 && x1 <= r1x2 && y2 >= r1y1 && y2 <= r1y2) {
			return true;
		}

	}

	// x/y is bottom left
	int x;
	int y;
	int width;
	int height;
};

// Will add more types as necessary
enum SquareType {
	ST_VOID,
	ST_EMPTY
};

struct GridSquare {
	SquareType type;
};

class Level {
public:
	Level();
	virtual ~Level();

	virtual void Generate(int w, int h, int numRooms);
	virtual GridSquare* SquareAt(int x, int y);
	virtual bool IsSquareOpen(int x, int y);

	virtual int GetWidth();
	virtual int GetHeight();

protected:
	virtual Room** GenerateNonOverlappingRooms(int numRooms);
	GridSquare*** m_grid;
	int m_width;
	int m_height;
};

#endif
