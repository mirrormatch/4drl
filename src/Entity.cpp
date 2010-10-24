
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
