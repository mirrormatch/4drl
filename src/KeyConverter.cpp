
#include "KeyConverter.h"

KeyConverter* KeyConverter::sm_instance = NULL;

KeyConverter* KeyConverter::Instance() {
	if(KeyConverter::sm_instance == NULL) {
		KeyConverter::sm_instance = new KeyConverter();
		KeyConverter::sm_instance->Initialize();
	}

	return KeyConverter::sm_instance;
}

KeyConverter::KeyConverter() {
}

void KeyConverter::Initialize() {
	m_keys[KEY_UP] = K_UP;
	m_keys[KEY_DOWN] = K_DOWN;
	m_keys[KEY_LEFT] = K_LEFT;
	m_keys[KEY_RIGHT] = K_RIGHT;

	m_keys['k'] = K_UP;
	m_keys['j'] = K_DOWN;
	m_keys['h'] = K_LEFT;
	m_keys['l'] = K_RIGHT;

	m_keys['8'] = K_UP;
	m_keys['2'] = K_DOWN;
	m_keys['4'] = K_LEFT;
	m_keys['6'] = K_RIGHT;

	m_keys[' '] = K_NEXT_TURN;
	m_keys['a'] = K_ATTACK;
	m_keys['c'] = K_CLEAR; // only used in debugging
	m_keys['d'] = K_DISCARD;
	m_keys['i'] = K_INVENTORY;
	m_keys['t'] = K_TARGET_MODE;
	m_keys['q'] = K_QUIT;
	m_keys['x'] = K_EXIT;
	m_keys['?'] = K_HELP;

	m_keys['\n'] = K_SELECT;
	m_keys['\r'] = K_SELECT;
	m_keys[KEY_ENTER] = K_SELECT;
	m_keys[PADENTER] = K_SELECT;

	m_keys[KEY_BACKSPACE] = K_BACKSPACE;
	m_keys['\b'] = K_BACKSPACE;
}

KeyConverter::~KeyConverter() {
}

KeyType KeyConverter::KeyForInput(int ch) {
	if(m_keys.find(ch) == m_keys.end()) {
		return K_NOT_FOUND;
	}

	return m_keys[ch];
}

