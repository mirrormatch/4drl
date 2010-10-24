

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "GeneralIncludes.h"
#include "CompoundRoom.h"

// Will add more types as necessary
enum SquareType {
	ST_VOID,
	ST_EMPTY,
	ST_WALL,
	ST_TEST_COORIDOR
};

class Entity;

struct GridSquare {
	SquareType type;
	Entity* entity;
};

class Room;

class Level {
public:
	Level(int num);
	virtual ~Level();

	virtual void Generate(int w, int h, int numRooms);
	virtual GridSquare* SquareAt(int x, int y);
	virtual bool IsSquareOpen(int x, int y);

	virtual int GetWidth();
	virtual int GetHeight();

	virtual int GetNumRooms();
	virtual int GetLevelNumber();
	virtual Entity* EntityAt(int x, int y);

protected:
	virtual Room** GenerateInitialRooms(int numRooms);
	virtual CompoundRoomVector* MergeBasicRooms(int numRooms, Room** rooms);
	virtual void CreateCooridor(CompoundRoom* first, CompoundRoom* second);
	virtual void CreateWalls();
	virtual bool AnyAdjacentAreFloors(int x, int y);
	GridSquare*** m_grid;
	int m_width;
	int m_height;
	int m_numRooms;
	int m_levelNumber;
};

#endif
