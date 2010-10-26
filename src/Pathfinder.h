
#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_

#include "Node.h"

class Level;

class Pathfinder {
public:
	static Pathfinder* Instance();
	void PopulateWithLevel(Level* level);
	NodeList* PathBetweenPoints(int x1, int y1, int x2, int y2);
	void Reset();
protected:
	Pathfinder();
	virtual ~Pathfinder();
	void DeleteExistingData();
	void PopulateListWithNodes(NodeList& toPopulate);
	void ResetNodes(NodeList& toReset, int dx, int dy);
	static Pathfinder* sm_instance;
	Node*** m_nodeMap;
	Level* m_currentLevel;
};

#endif
