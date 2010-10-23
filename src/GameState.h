
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class View;

class GameState {
	public:
		GameState();
		virtual ~GameState();

		void Initialize();
		void Update();
		bool IsRunning();
		void RequestQuit();

	private:
		bool m_isRunning;
		View* m_currentView;
};

#endif
