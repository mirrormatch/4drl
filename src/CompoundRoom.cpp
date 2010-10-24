
#include "CompoundRoom.h"
#include "Room.h"

CompoundRoom::CompoundRoom() : 
	m_x(0), m_y(0), m_width(0), m_height(0), m_data(NULL){
}

CompoundRoom::~CompoundRoom() {
}

void CompoundRoom::Initialize(Room* firstRoom) {
	m_x = firstRoom->x;
	m_y = firstRoom->y;
	m_width = firstRoom->width;
	m_height = firstRoom->height;
	m_data = new bool*[m_width];
	for(int x = 0; x < m_width; x++) {
		m_data[x] = new bool[m_height];
		for(int y = 0; y < m_height; y++) {
			// every spot is filled on init
			m_data[x][y] = true;
		}
	}
}

bool CompoundRoom::Overlaps(Room* r) {
	// need to do the piece by piece check
	for(int x = m_x; x < m_x + m_width; x++) {
		for(int y = m_y; y < m_y + m_height; y++) {
			if(m_data[x - m_x][y - m_y] && r->ContainsPoint(x, y)) {
				return true;
			}
		}
	}

	return false;
}

bool CompoundRoom::OverlapsOrAdjacent(Room* r) {
	// piece by piece check
	for(int x = m_x; x < m_x + m_width; x++) {
		for(int y = m_y; y < m_y + m_height; y++) {
			if(m_data[x - m_x][y - m_y] && r->ContainsPoint(x, y)) {
				return true;
			}
		}
	}

	// If we still haven't found something, check to see if we're adjacent
	for(int y = m_y; y < m_y + m_height; y++) {
		if(r->ContainsPoint(m_x - 1, y) || r->ContainsPoint(m_x + m_width + 1, y)) {
			return true;
		}
	}
	for(int x = m_x; x < m_x + m_width; x++) {
		if(r->ContainsPoint(x, m_y - 1) || r->ContainsPoint(x, m_y + m_height + 1)) {
			return true;
		}
	}

	return false;
}

void CompoundRoom::Merge(Room* r) {
	// Figure out the new maximal bounds
	int lx = (m_x < r->x) ? m_x : r->x;
	int ly = (m_y < r->y) ? m_y : r->y;
	int ex = m_x + m_width;
	int ey = m_y + m_height;
	if(r->x + r->width > ex) {
		ex = r->x + r->width;
	}
	if(r->y + r->height > ey) {
		ey = r->y + r->height;
	}
	int width = ex - lx;
	int height = ey - ly;

	// prep the new data array
	bool** newData = new bool*[width];
	for(int x = 0; x < width; x++) {
		newData[x] = new bool[height];
		for(int y = 0; y < height; y++) {
			newData[x][y] = false;
		}
	}

	// copy over the old data
	int oldStartX = m_x - lx;
	int oldStartY = m_y - ly;
	for(int x = oldStartX; x < oldStartX + m_width; x++) {
		for(int y = oldStartY; y < oldStartY + m_height; y++) {
			newData[x][y] = m_data[x - oldStartX][y - oldStartY];
		}
	}

	// copy in the new room
	oldStartX = r->x - lx;
	oldStartY = r->y - ly;
	for(int x = oldStartX; x < oldStartX + r->width; x++) {
		for(int y = oldStartY; y < oldStartY + r->height; y++) {
			newData[x][y] = true;
		}
	}

	// delete the old room
	for(int x = 0; x < m_width; x++) {
		delete [] m_data[x];
	}
	delete [] m_data;

	// copy over the new values
	m_x = lx;
	m_y = ly;
	m_width = width;
	m_height = height;
	m_data = newData;
}

bool CompoundRoom::IsFilled(int x, int y) {
	if(x >= m_x && x < m_x + m_width && y >= m_y && y < m_y + m_height) {
		return m_data[x - m_x][y - m_y];
	}
	return false;
}

int CompoundRoom::GetX() {
	return m_x;
}

int CompoundRoom::GetY() {
	return m_y;
}

int CompoundRoom::GetWidth() {
	return m_width;
}

int CompoundRoom::GetHeight() {
	return m_height;
}

void CompoundRoom::ClosestPointToMiddle(int* x, int* y) {
	int testX = m_x + m_width / 2;
	int testY = m_y + m_height / 2;
	*x = testX;
	*y = testY;
	// FIXME: test to make sure point is valid, and circle around until you find
	// valid one
}

void CompoundRoom::GetRandomValidPoint(int* x, int* y) {
	int tx = (rand() % m_width) + m_x;
	int ty = (rand() % m_height) + m_y;
	while(!IsFilled(tx, ty)) {
		tx = (rand() % m_width) + m_x;
		ty = (rand() % m_height) + m_y;
	}
	*x = tx;
	*y = ty;
}
