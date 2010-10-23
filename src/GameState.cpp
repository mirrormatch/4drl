
#include "GameState.h"
#include "View.h"

GameState::GameState() : m_isRunning(true), m_currentView(NULL) {
}

GameState::~GameState() {
}

void GameState::Initialize() {
	// use this for any init that isn't simple variable defaults
	m_currentView = new View(80, 24);
}

void GameState::Update() {
	// At some point this will need to key off of states/transitions, but for
	// now we're just hardcoding a ref to the mainview
	m_currentView->Update();
	m_currentView->Draw();
}

bool GameState::IsRunning() {
	return m_isRunning;
}

