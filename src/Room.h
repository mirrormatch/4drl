
#ifndef _ROOM_H_
#define _ROOM_H_

class Room {
public:
	Room(int x, int y, int w, int h);
	virtual ~Room();
	virtual bool Overlaps(Room* r1);
	virtual bool ContainsPoint(int ax, int ay);

	// x/y is top left
	int x;
	int y;
	int width;
	int height;
};

#endif
