
#include "Entity.h"
#include <math.h>

Entity::Entity(char c, int df, EntityClass cls) : 
	m_dispChar(c), m_dispFlags(df), m_class(cls), m_isPassable(true) {
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

string& Entity::GetDisplayName() {
	return m_displayName;
}

void Entity::SetDisplayName(string name) {
	m_displayName = name;
}

bool Entity::IsPassable() {
	return m_isPassable;
}

void Entity::SetIsPassable(bool val) {
	m_isPassable = val;
}

int Entity::DistanceTo(Entity* e) {
	int x = m_x - e->m_x;
	int y = m_y - e->m_y;
	return sqrt((double)(x * x + y * y));
}

bool Entity::ShouldRemove() {
	return false;
}

void Entity::Kill() {
	// do nothing by default
}

void Entity::SetDisplayChar(char ch) {
	m_dispChar = ch;
}
