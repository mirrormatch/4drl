

#include "Entrance.h"
#include "DataManager.h"

Entrance::Entrance() : Entity('^', GREEN_BOLD, E_ENTRANCE) {
}

Entrance::~Entrance() {
}

void Entrance::Update() {
}

void Entrance::Activate() {
	DataManager::Instance()->GoToPrevLevel();
}
