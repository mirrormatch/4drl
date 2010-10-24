
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class View;

class GameState {
	public:
		GameState(unsigned long seed = 0);
		virtual ~GameState();

		void Initialize();
		void Update();
		bool IsRunning();
		void RequestQuit();

	private:
		unsigned long m_seed;
		bool m_isRunning;
		View* m_currentView;
};

#endif
