
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

bool Sight::CanSee(Entity* e1, Entity* e2) {
	if(e1 == e2) {
		return true; // you can see yourself, I guess?
	}

	int x1 = e1->GetX(); int y1 = e1->GetY();
	int x2 = e2->GetX(); int y2 = e2->GetY();
	if(x1 == x2 && y1 == y2) {
		return true; // if you're stacked somehow, you can see
	}

	bool isSteep = abs(y2 - y1) > abs(x2 - x1);
	if(isSteep) {
		int tmp = x1;
		x1 = y1;
		y1 = tmp;

		tmp = x2;
		x2 = y2;
		y2 = tmp;
	}
	if(x1 > x2) {
		int tmp = x1;
		x1 = x2;
		x2 = tmp;

		tmp = y1;
		y1 = y2;
		y2 = y1;
	}
	int deltax = x2 - x1;
	int deltay = abs(y2 - y1);
	int error = (int)(deltax / 2.0);
	int y = y1;
	int ystep = (y1 < y2) ? 1 : -1;
	for(int x = x1; x < x2; x++) {
		if(isSteep) {
			// check y,x
			if(m_level->SquareAt(y, x)->type != ST_EMPTY) {
				return false;
			}
		}
		else {
			// check x, y
			if(m_level->SquareAt(x, y)->type != ST_EMPTY) {
				return false;
			}
		}
		error -= deltay;
		if(error < 0) {
			y += ystep;
			error += deltax;
		}
	}

	return true;
}

