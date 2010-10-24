
#ifndef _MAIN_VIEW_H_
#define _MAIN_VIEW_H_

#include "View.h"

class Level;

class MainView : public View {
	public:
		MainView(GameState* gs, int w, int h);
		virtual ~MainView();
		virtual void Initialize();

		virtual void RequestInput();
		virtual void Update();

	protected:
		int m_scrollX;
		int m_scrollY;
};

#endif
