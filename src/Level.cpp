
#include "Level.h"
#include "Room.h"

Level::Level() {
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
		}
	}

	Room** rooms = GenerateInitialRooms(numRooms);
	CompoundRoomVector* crs = MergeBasicRooms(numRooms, rooms);
	for(int i = 0; i < numRooms; i++) {
		delete rooms[i];
	}
	delete [] rooms;

	for(unsigned int i = 0; i < crs->size(); i++) {
		CompoundRoom* cr = (*crs)[i];
		for(int x = cr->GetX(); x < cr->GetX() + cr->GetWidth(); x++) {
			for(int y = cr->GetY(); y < cr->GetY() + cr->GetHeight(); y++) {
				if(cr->IsFilled(x, y)) {
					m_grid[x][y]->type = ST_EMPTY;
				}
			}
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
			for(list<Room*>::iterator i = roomList.begin();  i != roomList.end(); i++) {
				Room* toCheck = *i;
				if(cr->Overlaps(toCheck)) {
					cr->Merge(toCheck);
					didAdd = true;
					roomList.erase(i);
					break;
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
	return m_grid[x][y]->type != ST_VOID;
}

int Level::GetWidth() {
	return m_width;
}

int Level::GetHeight() {
	return m_height;
}
