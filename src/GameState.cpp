
#include "GameState.h"
#include "View.h"

GameState::GameState() : m_isRunning(true), m_currentView(NULL) {
}

GameState::~GameState() {
	if(m_currentView) {
		delete m_currentView;
	}
}

void GameState::Initialize() {
	// use this for any init that isn't simple variable defaults
	m_currentView = new View(this, 80, 24);
	m_currentView->Initialize();
}

void GameState::Update() {
	// At some point this will need to key off of states/transitions, but for
	// now we're just hardcoding a ref to the mainview
	if(m_isRunning) {
		m_currentView->Update();
		m_currentView->Draw();
		m_currentView->RequestInput();
	}
}

bool GameState::IsRunning() {
	return m_isRunning;
}

void GameState::RequestQuit() {
	m_isRunning = false;
}
