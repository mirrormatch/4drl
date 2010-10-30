

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "GeneralIncludes.h"
#include "CompoundRoom.h"
#include "Entity.h"

// Will add more types as necessary
enum SquareType {
	ST_VOID,
	ST_EMPTY,
	ST_WALL,
	ST_TEST_COORIDOR
};

class Entrance;
class Exit;

struct GridSquare {
	SquareType type;
	Entity* entity;
	bool debugFlag;
	bool hasBeenSeen;
	bool inView;
};

class Room;

class Level {
public:
	Level(int num);
	virtual ~Level();

	virtual void Generate(int w, int h, int numRooms);
	virtual GridSquare* SquareAt(int x, int y);
	virtual bool IsSquareOpen(int x, int y, bool avoidItems = false);

	virtual int GetWidth();
	virtual int GetHeight();

	virtual int GetNumRooms();
	virtual int GetLevelNumber();
	virtual Entity* EntityAt(int x, int y);

	virtual Entrance* GetEntrance();
	virtual Exit* GetExit();
	virtual void RemoveEntity(Entity* toRemove);
	virtual void AddEntity(Entity* toAdd);
	virtual void ResetDebugFlags();
	virtual bool AnyAdjacentAreFloors(int x, int y);
	virtual bool AnyAdjacentAreVisible(int x, int y);

	virtual void Update();

	virtual void ResetVisibility();
	virtual void LightArea(int x, int y, int xrange, int yrange);
	virtual EntityList* MonstersInRange(int tx, int ty, int xrange, int yrange);

protected:
	virtual Room** GenerateInitialRooms(int numRooms);
	virtual CompoundRoomVector* MergeBasicRooms(int numRooms, Room** rooms);
	virtual void CreateCooridor(CompoundRoom* first, CompoundRoom* second);
	virtual void CreateWalls();
	virtual void CreateExits(CompoundRoom* first, CompoundRoom* last);
	GridSquare*** m_grid;
	int m_width;
	int m_height;
	int m_numRooms;
	int m_levelNumber;
	Entrance* m_entrance;
	Exit* m_exit;
	EntityList m_entities;
};

#endif
