
#include "Level.h"

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

	Room** rooms = GenerateNonOverlappingRooms(numRooms);
	for(int i = 0; i < numRooms; i++) {
		Room* r = rooms[i];
		for(int x = r->x; x < r->x + r->width; x++) {
			for(int y = r->y; y < r->y + r->height; y++) {
				m_grid[x][y]->type = ST_EMPTY;
			}
		}
	}
}

Room** Level::GenerateNonOverlappingRooms(int numRooms) {
	// FIXME: for now, overlap, i don't care
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

GridSquare* Level::SquareAt(int x, int y) {
	return m_grid[x][y];
}

bool Level::IsSquareOpen(int x, int y) {
	// FIXME: Eventually needs to take other things into account
	return m_grid[x][y]->type != ST_VOID;
}

