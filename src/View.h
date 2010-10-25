
#ifndef _VIEW_H_
#define _VIEW_H_

#include "GeneralIncludes.h"

class GameState;

class View;
typedef map<string, View*> ViewMap;
typedef ViewMap::iterator ViewMapIter;

class View {
	public:
		View(GameState* parent, int w, int h);
		virtual ~View();
		virtual void Initialize();

		virtual bool RequestInput();
		virtual void Draw();
		virtual void SetCharAt(int x, int y, char value, int flags = 0);
		virtual void SetStringAt(int x, int y, string& value, int flags = 0);
		virtual void Clear();
		virtual void ClearWith(char ch, int flags = 0);
		virtual void Update();
		virtual void ResetState();

		virtual void SetCursorVisible(bool isVisible);
		virtual void SetCursorPosition(int x, int y);

	protected:
		GameState* m_parent;
		int m_width;
		int m_height;
		char** m_screenData;
		unsigned int** m_screenAttrs;
		char start;

		int m_cursorX;
		int m_cursorY;
		bool m_visibleCursor;
};

#endif
