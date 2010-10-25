
#ifndef _MAIN_VIEW_H_
#define _MAIN_VIEW_H_

#include "View.h"

class Level;
class Player;

enum MVInputState {
	MVIS_MAIN,
	MVIS_TARGET_SELECT
};

class MainView : public View {
	public:
		MainView(GameState* gs, int w, int h);
		virtual ~MainView();
		virtual void Initialize();

		virtual bool RequestInput();
		virtual void Update();

	protected:
		virtual bool HandleMainInput(int ch);
		virtual bool HandleTargetSelectInput(int ch);
		virtual void DrawStats(Player* p);
		int m_scrollX;
		int m_scrollY;
		MVInputState m_state;
};

#endif
