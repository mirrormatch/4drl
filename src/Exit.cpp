

#include "Exit.h"
#include "DataManager.h"

Exit::Exit() : Entity('v', GREEN_BOLD, E_EXIT) {
}

Exit::~Exit() {
}

void Exit::Update() {
}

void Exit::Activate() {
	DataManager::Instance()->GoToNextLevel();
}
