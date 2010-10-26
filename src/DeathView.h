
#ifndef _DEATH_VIEW_H_
#define _DEATH_VIEW_H_

#include "View.h"

class DeathView : public View {
public:
	DeathView(GameState* gs, int w, int h);
	virtual ~DeathView();
	virtual void Initialize();
	virtual bool RequestInput();
	virtual void Update();
	virtual void ResetState();

};

#endif
