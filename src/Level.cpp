
#include "Level.h"
#include "Room.h"
#include "Entrance.h"
#include "Exit.h"

Level::Level(int num) : m_levelNumber(num) {
}

Level::~Level() {
}

void Level::Generate(int w, int h, int numRooms) {
	m_width = w;
	m_height = h;
	m_grid = new GridSquare**[m_width];
	for(int x = 0; x < m_width; x++) {
		m_grid[x] = new GridSquare*[m_height];
		for(int y = 0; y < m_height; y++) {
			m_grid[x][y] = new GridSquare();
			m_grid[x][y]->type = ST_VOID;
			m_grid[x][y]->entity = NULL;
		}
	}

	// Create the initial boxes
	Room** rooms = GenerateInitialRooms(numRooms);

	// Merge the boxes into compound rooms
	CompoundRoomVector* crs = MergeBasicRooms(numRooms, rooms);

	// clean up the inital boxes
	for(int i = 0; i < numRooms; i++) {
		delete rooms[i];
	}
	delete [] rooms;

	// Plot the compound rooms
	for(unsigned int i = 0; i < crs->size(); i++) {
		CompoundRoom* cr = (*crs)[i];
		cr->GenerateItems();
		for(int x = cr->GetX(); x < cr->GetX() + cr->GetWidth(); x++) {
			for(int y = cr->GetY(); y < cr->GetY() + cr->GetHeight(); y++) {
				if(cr->IsFilled(x, y)) {
					m_grid[x][y]->type = ST_EMPTY;
					if(cr->EntityAt(x, y)) {
						m_grid[x][y]->entity = cr->EntityAt(x, y);
					}
				}
			}
		}
	}

	// If we've got more than one room, make cooridors
	m_numRooms = crs->size();
	if(crs->size() > 1) {
		for(unsigned int i = 0; i < crs->size() - 1; i++) {
			CompoundRoom* first = (*crs)[i];
			CompoundRoom* second = (*crs)[i+1];
			CreateCooridor(first, second);
		}
	}

	// Plot the walls around the rooms and cooridors
	CreateWalls();

	// Create the basic openings in the level
	CompoundRoom* first = crs->front();
	CompoundRoom* last = crs->back();
	CreateExits(first, last);
}

void Level::CreateExits(CompoundRoom* first, CompoundRoom* last) {
	int x, y;
	first->GetRandomValidPoint(&x, &y);
	m_entrance = new Entrance();
	m_entrance->SetPosition(x, y);
	m_grid[x][y]->entity = m_entrance;
	last->GetRandomValidPoint(&x, &y);
	m_exit = new Exit();
	m_exit->SetPosition(x, y);
	m_grid[x][y]->entity = m_exit;
}

void Level::CreateWalls() {
	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			GridSquare* gs = m_grid[x][y];
			if(gs->type == ST_VOID) {
				if(AnyAdjacentAreFloors(x,y)) {
					gs->type= ST_WALL;
				}
			}
		}
	}
}

bool Level::AnyAdjacentAreFloors(int x, int y) {
	for(int tx = x - 1; tx <= x + 1; tx++) {
		for(int ty = y - 1; ty <= y + 1; ty++) {
			if(tx == x && ty == y) {
				continue;
			}
			if(IsSquareOpen(tx, ty)) {
				return true;
			}
		}
	}
	return false;
}

void Level::CreateCooridor(CompoundRoom* first, CompoundRoom* second) {
	int x1, y1;
	int x2, y2;
	first->ClosestPointToMiddle(&x1, &y1);
	second->ClosestPointToMiddle(&x2, &y2);
	if(x1 >= x2 && y1 >= y2) {
		for(int x = x2; x <= x1; x++) {
			m_grid[x][y2]->type = ST_EMPTY;
		}
		for(int y = y2; y <= y1; y++) {
			m_grid[x1][y]->type = ST_EMPTY;
		}
	}
	else if(x1 >= x2 && y1 < y2) {
		for(int x = x2; x <= x1; x++) {
			m_grid[x][y2]->type = ST_EMPTY;
		}
		for(int y = y1; y <= y2; y++) {
			m_grid[x1][y]->type = ST_EMPTY;
		}
	}
	else if(x1 < x2 && y1 >= y2) {
		for(int x = x1; x <= x2; x++) {
			m_grid[x][y1]->type = ST_EMPTY;
		}
		for(int y = y2; y <= y1; y++) {
			m_grid[x2][y]->type = ST_EMPTY;
		}
	}
	else if(x1 < x2 && y1 < y2) {
		for(int x = x1; x <= x2; x++) {
			m_grid[x][y1]->type = ST_EMPTY;
		}
		for(int y = y1; y <= y2; y++) {
			m_grid[x2][y]->type = ST_EMPTY;
		}
	}
}

Room** Level::GenerateInitialRooms(int numRooms) {
	Room** toReturn = new Room*[numRooms];
	for(int i = 0; i < numRooms; i++) {
		int width = rand() % (m_width / 10) + 8;
		int height = rand() % (m_height / 10) + 8;
		int x = rand() % (m_width - width);
		int y = rand() % (m_height - height);
		toReturn[i] = new Room(x, y, width, height);
	}

	return toReturn;
}

CompoundRoomVector* Level::MergeBasicRooms(int numRooms, Room** rooms) {
	CompoundRoomVector* newRooms = new CompoundRoomVector();

	// load up a vector with the passed in rooms
	list<Room*> roomList;
	for(int i = 0; i < numRooms; i++) {
		roomList.push_back(rooms[i]);
	}

	while(roomList.size() > 0) {
		Room* r = roomList.back();
		roomList.pop_back();
		CompoundRoom* cr = new CompoundRoom();
		cr->Initialize(r);
		bool didAdd = true;
		while(didAdd) {
			didAdd = false;
			list<Room*>::iterator i = roomList.begin();
			while(i != roomList.end()) {
				Room* toCheck = *i;
				if(cr->Overlaps(toCheck)) {
					cr->Merge(toCheck);
					didAdd = true;
					i = roomList.erase(i);
				}
				else {
					i++;
				}
			}
		}
		newRooms->push_back(cr);
	}

	return newRooms;
}

GridSquare* Level::SquareAt(int x, int y) {
	return m_grid[x][y];
}

bool Level::IsSquareOpen(int x, int y) {
	// FIXME: Eventually needs to take other things into account
	if(x < 0 || x >= m_width || y < 0 || y >= m_height) {
		return false;
	}
	SquareType st = m_grid[x][y]->type;
	return st != ST_VOID && st != ST_WALL;
}

int Level::GetWidth() {
	return m_width;
}

int Level::GetHeight() {
	return m_height;
}

int Level::GetNumRooms() {
	return m_numRooms;
}

Entity* Level::EntityAt(int x, int y) {
	return m_grid[x][y]->entity;
}

int Level::GetLevelNumber() {
	return m_levelNumber;
}

Entrance* Level::GetEntrance() {
	return m_entrance;
}

Exit* Level::GetExit() {
	return m_exit;
}
