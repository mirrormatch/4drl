
#ifndef _VIEW_H_
#define _VIEW_H_

#include "GeneralIncludes.h"

class View {
	public:
		View(int w, int h);
		virtual ~View();
		virtual void Initialize();

		virtual void RequestInput();
		virtual void Draw();
		virtual void SetCharAt(int x, int y, char value, int flags);
		virtual void SetStringAt(int x, int y, string& value, int flags);
		virtual void Clear();
		virtual void Update();

	protected:
		char** m_screenData;
		int m_width;
		int m_height;
};

#endif
