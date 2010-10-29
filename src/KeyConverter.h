
#ifndef _KEY_CONVERTER_H_
#define _KEY_CONVERTER_H_

#include "GeneralIncludes.h"

enum KeyType {
	K_NOT_FOUND,
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_QUIT,
	K_TARGET_MODE,
	K_ATTACK,
	K_INVENTORY,
	K_SELECT,
	K_DISCARD,
	K_BACKSPACE,
	K_EXIT,
	K_CLEAR,
	K_NEXT_TURN,
	K_HELP
};

typedef unordered_map<int, KeyType> KeyMap;

class KeyConverter {
public:
	static KeyConverter* Instance();
	KeyType KeyForInput(int ch);

protected:
	static KeyConverter* sm_instance;

	KeyConverter();
	virtual ~KeyConverter();
	virtual void Initialize();
	KeyMap m_keys;
};

#endif
