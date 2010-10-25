
#ifndef _PLAYER_CREATE_VIEW_H_
#define _PLAYER_CREATE_VIEW_H_

#include "GeneralIncludes.h"
#include "View.h"

enum PCState {
	PC_NAME,
	PC_CLASS
};

class PlayerCreateView : public View {
	public:
		PlayerCreateView(GameState* gs, int w, int h);
		virtual ~PlayerCreateView();
		virtual void Initialize();

		virtual void RequestInput();
		virtual void Update();

	protected:
		virtual void HandleNameInput(int ch);
		virtual void HandleClassInput(int ch);
		virtual void DrawNameScreen();
		virtual void DrawClassScreen();
		PCState m_state;
		string m_name;
		unsigned int m_selectIdx;
};

#endif
