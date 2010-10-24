
#include "Room.h"

Room::Room(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {
}

Room::~Room() {
}

bool Room::Overlaps(Room* r1) {
	int x1 = x; int x2 = x + width;
	int y1 = y; int y2 = y + height;
	int r1x1 = r1->x; int r1x2 = r1->x + width;
	int r1y1 = r1->y; int r1y2 = r1->y + height;

	// Check to see if any of the points of r1 overlap this room
	if(ContainsPoint(r1x1, r1y1)) {
		return true;
	}
	else if(ContainsPoint(r1x1, r1y2)) {
		return true;
	}
	else if(ContainsPoint(r1x2, r1y2)) {
		return true;
	}
	else if(ContainsPoint(r1x2, r1y1)) {
		return true;
	}

	// Now checking the other way -- in case this room is contained in r1
	if(r1->ContainsPoint(x1, y1)) {
		return true;
	}
	else if(r1->ContainsPoint(x1, y2)) {
		return true;
	}
	else if(r1->ContainsPoint(x2, y2)) {
		return true;
	}
	else if(r1->ContainsPoint(x2, y1)) {
		return true;
	}
	return false;
}

bool Room::ContainsPoint(int ax, int ay) {
	return (ax >= x && ax <= x + width && ay >= y && ay <= y + height);
}
