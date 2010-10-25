
#ifndef _COMPOUND_ROOM_H_
#define _COMPOUND_ROOM_H_

#include "GeneralIncludes.h"

class Room;
class Entity;
class CompoundRoom;

typedef vector<CompoundRoom*> CompoundRoomVector;

class CompoundRoom {
public:
	CompoundRoom();
	virtual ~CompoundRoom();

	void Initialize(Room* firstRoom);

	bool Overlaps(Room* r);
	bool OverlapsOrAdjacent(Room* r);
	void Merge(Room* r);
	bool IsFilled(int x, int y);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	void ClosestPointToMiddle(int* x, int* y);
	void GetRandomValidPoint(int* x, int* y);

	Entity* EntityAt(int x, int y);

	void GenerateItems();

protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	Entity*** m_entities;
	bool** m_data;
};

#endif
