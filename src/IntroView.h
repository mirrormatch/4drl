
#ifndef _INTRO_VIEW_H_
#define _INTRO_VIEW_H_

#include "View.h"

class IntroView : public View {
	public:
		IntroView(GameState* gs, int w, int h);
		virtual ~IntroView();
		virtual void Initialize();

		virtual void RequestInput();
		virtual void Update();
};

#endif
