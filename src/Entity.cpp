
#include "Entity.h"

Entity::Entity(char c, int df) : m_dispChar(c), m_dispFlags(df) {
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
