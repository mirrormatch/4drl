
#ifndef _MAIN_VIEW_H_
#define _MAIN_VIEW_H_

#include "View.h"

class Level;
class Player;

class MainView : public View {
	public:
		MainView(GameState* gs, int w, int h);
		virtual ~MainView();
		virtual void Initialize();

		virtual void RequestInput();
		virtual void Update();

	protected:
		virtual void DrawStats(Player* p);
		int m_scrollX;
		int m_scrollY;
};

#endif
