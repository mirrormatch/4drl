
#include "Sight.h"
#include "Entity.h"
#include "Level.h"
#include <math.h>

Sight* Sight::sm_instance = NULL;

Sight* Sight::Instance() {
	if(Sight::sm_instance == NULL) {
		Sight::sm_instance = new Sight();
	}
	return Sight::sm_instance;
}

Sight::Sight() {
}

Sight::~Sight() {
}

void Sight::SetCurrentLevel(Level* l) {
	m_level = l;
}

bool Sight::CanSee(Entity* e1, Entity* e2, bool debug) {
	if(e1 == e2) {
		return true; // you can see yourself, I guess?
	}

	int x0 = e1->GetX(); int y0 = e1->GetY();
	int x1 = e2->GetX(); int y1 = e2->GetY();
	return CanSee(x0, y0, x1, y1, debug);
}

bool Sight::CanSee(int x0, int y0, int x1, int y1, bool debug) {
	if(x0 == x1 && y0 == y1) {
		return true; // if you're stacked somehow, you can see
	}

	bool isSteep = abs(y1 - y0) > abs(x1 - x0);
	if(isSteep) {
		int tmp = x0;
		x0 = y0;
		y0 = tmp;

		tmp = x1;
		x1 = y1;
		y1 = tmp;
	}
	if(x0 > x1) {
		int tmp = x0;
		x0 = x1;
		x1 = tmp;

		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	int error = deltax / 2;
	int y = y0;
	int ystep = (y0 < y1) ? 1 : -1;
	// Not <= because I don't need to check the dest
	bool first = true;
	for(int x = x0; x < x1; x++) {
		if(isSteep) {
			// check y, x
			if(!first && m_level->SquareAt(y, x)->type != ST_EMPTY) {
				return false;
			}
		}
		else {
			// check x, y
			if(!first && m_level->SquareAt(x, y)->type != ST_EMPTY) {
				return false;
			}
		}
		error -= deltay;
		if(error < 0) {
			y += ystep;
			error += deltax;
		}
		first = false;
	}

	return true;
}
