
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "View.h"

enum StateType {
	GAME_STATE_INITIAL,
	GAME_STATE_INTRO,
	GAME_STATE_PLAYER_CREATE,
	GAME_STATE_INVENTORY,
	GAME_STATE_MAIN
};

class GameState {
	public:
		GameState(unsigned long seed = 0);
		virtual ~GameState();

		void Initialize();
		void Update();
		bool IsRunning();
		void RequestQuit();

		void ChangeState(StateType newState);

	private:
		unsigned long m_seed;
		bool m_isRunning;
		View* m_currentView;
		StateType m_state;
		ViewMap m_views;
};

#endif
