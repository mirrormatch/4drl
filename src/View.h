
#ifndef _VIEW_H_
#define _VIEW_H_

#include "GeneralIncludes.h"

class GameState;

class View {
	public:
		View(GameState* parent, int w, int h);
		virtual ~View();
		virtual void Initialize();

		virtual void RequestInput();
		virtual void Draw();
		virtual void SetCharAt(int x, int y, char value, int flags);
		virtual void SetStringAt(int x, int y, string& value, int flags);
		virtual void Clear();
		virtual void ClearWith(char ch, int flags = 0);
		virtual void Update();

	protected:
		GameState* m_parent;
		int m_width;
		int m_height;
		char** m_screenData;
		char start;
};

#endif
