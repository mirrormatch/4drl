

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "GeneralIncludes.h"
#include "CompoundRoom.h"

// Will add more types as necessary
enum SquareType {
	ST_VOID,
	ST_EMPTY
};

struct GridSquare {
	SquareType type;
};

class Room;

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
	virtual Room** GenerateInitialRooms(int numRooms);
	virtual CompoundRoomVector* MergeBasicRooms(int numRooms, Room** rooms);
	GridSquare*** m_grid;
	int m_width;
	int m_height;
};

#endif
