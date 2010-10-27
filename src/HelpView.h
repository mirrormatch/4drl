
#ifndef _HELP_VIEW_H_
#define _HELP_VIEW_H_

#include "View.h"

class HelpView : public View {
public:
		HelpView(GameState* gs, int w, int h);
		virtual ~HelpView();
		virtual void Initialize();
		virtual bool RequestInput();
		virtual void Update();
};

#endif
