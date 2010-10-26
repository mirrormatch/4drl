
#include "Pathfinder.h"
#include "Level.h"

Pathfinder* Pathfinder::sm_instance = NULL;

Pathfinder* Pathfinder::Instance() {
	if(Pathfinder::sm_instance == NULL) {
		Pathfinder::sm_instance = new Pathfinder();
	}
	return Pathfinder::sm_instance;
}

Pathfinder::Pathfinder() : m_nodeMap(NULL), m_currentLevel(NULL) {
}

Pathfinder::~Pathfinder() {
	DeleteExistingData();
}

void Pathfinder::Reset() {
	DeleteExistingData();
}

void Pathfinder::PopulateWithLevel(Level* level) {
	DeleteExistingData();
	m_currentLevel = level;
	m_nodeMap = new Node**[level->GetWidth()];
	for(int x = 0; x < level->GetWidth(); x++) {
		m_nodeMap[x] = new Node*[level->GetHeight()];
		for(int y = 0; y < level->GetHeight(); y++) {
			// Only create nodes for floor tiles
			if(level->SquareAt(x, y)->type == ST_EMPTY) {
				m_nodeMap[x][y] = new Node(x, y);
				m_nodeMap[x][y]->SetSquare(level->SquareAt(x, y));
			}
			else {
				m_nodeMap[x][y] = NULL;
			}
		}
	}
}

void Pathfinder::DeleteExistingData() {
	if(m_nodeMap) {
		for(int x = 0; x < m_currentLevel->GetWidth(); x++) {
			for(int y = 0; y < m_currentLevel->GetHeight(); y++) {
				delete m_nodeMap[x][y];
			}
			delete [] m_nodeMap[x];
		}
		delete [] m_nodeMap;
		m_nodeMap = NULL;
		m_currentLevel = NULL;
	}
}

NodeList* Pathfinder::PathBetweenPoints(int x1, int y1, int x2, int y2) {

	// Set up all the data structures we need, lots o' stuff
	NodeList Q;
	PreviousNodeMap prev;
	PopulateListWithNodes(Q);
	ResetNodes(Q, x2, y2);
	Node* source = m_nodeMap[x1][y1];
	source->SetDistance(0);
	Node* dest = m_nodeMap[x2][y2];

	while(Q.size() > 0) {
		Q.sort(NodesByScore);
		Node* u = Q.front();
		if(u == dest) {
			// found our node, break!
			break;
		}
		if(u->GetDistance() == NODE_INFINITY) {
			// In this case, no valid path from point 1 to point 2
			return NULL;
		}

		// Remove it from the unvisited queue
		Q.remove(u);

		// Update its neighbors
		int x = u->GetX();
		int y = u->GetY();

		if(x - 1 >= 0 && m_nodeMap[x-1][y]) {
			Node* toUpdate = m_nodeMap[x-1][y];
			if(u->GetDistance() + 1 < toUpdate->GetDistance()) {
				prev[toUpdate] = u;
				toUpdate->SetDistance(u->GetDistance() + 1);
			}
		}
		if(x + 1 < m_currentLevel->GetWidth() && m_nodeMap[x+1][y]) {
			Node* toUpdate = m_nodeMap[x+1][y];
			if(u->GetDistance() + 1 < toUpdate->GetDistance()) {
				prev[toUpdate] = u;
				toUpdate->SetDistance(u->GetDistance() + 1);
			}
		}
		if(y - 1 >= 0 && m_nodeMap[x][y-1]) {
			Node* toUpdate = m_nodeMap[x][y-1];
			if(u->GetDistance() + 1 < toUpdate->GetDistance()) {
				prev[toUpdate] = u;
				toUpdate->SetDistance(u->GetDistance() + 1);
			}
		}
		if(y + 1 < m_currentLevel->GetHeight() && m_nodeMap[x][y+1]) {
			Node* toUpdate = m_nodeMap[x][y+1];
			if(u->GetDistance() + 1 < toUpdate->GetDistance()) {
				prev[toUpdate] = u;
				toUpdate->SetDistance(u->GetDistance() + 1);
			}
		}
	}
	// Prep the list of path nodes to send back
	NodeList* toReturn = new NodeList();
	Node* next = prev[dest];
	toReturn->push_back(next);
	while(prev.find(next) != prev.end() && prev[next] != source) {
		next = prev[next];
		toReturn->push_back(next);
	}

	return toReturn;

}

void Pathfinder::ResetNodes(NodeList& toReset, int dx, int dy) {
	for(NodeList::iterator i = toReset.begin(); i != toReset.end(); i++) {
		Node* n = *i;
		n->SetDistance(NODE_INFINITY);
		n->CalculateHeuristic(dx, dy);
	}
}

void Pathfinder::PopulateListWithNodes(NodeList& toPopulate) {
	for(int x = 0; x < m_currentLevel->GetWidth(); x++) {
		for(int y = 0; y < m_currentLevel->GetHeight(); y++) {
			if(m_nodeMap[x][y]) {
				toPopulate.push_back(m_nodeMap[x][y]);
			}
		}
	}
}
