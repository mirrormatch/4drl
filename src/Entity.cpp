
#include "Entity.h"

Entity::Entity(char c, int df, EntityClass cls) : 
	m_dispChar(c), m_dispFlags(df), m_class(cls) {
}

Entity::~Entity() {
}

char Entity::GetDisplayChar() {
	return m_dispChar;
}

int Entity::GetDisplayFlags() {
	return m_dispFlags;
}

void Entity::SetPosition(int x, int y) {
	m_x = x;
	m_y = y;
}

int Entity::GetX() {
	return m_x;
}

int Entity::GetY() {
	return m_y;
}

EntityClass Entity::GetClass() {
	return m_class;
}
