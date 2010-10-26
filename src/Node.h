
#ifndef _NODE_H_
#define _NODE_H_

#include "GeneralIncludes.h"

#define NODE_INFINITY 999999

class Node;
struct GridSquare;

typedef list<Node*> NodeList;
typedef unordered_map<Node*, Node*> PreviousNodeMap;
bool NodesByDistance(Node* a, Node* b);

class Node {
public:
	Node(int x, int y);
	virtual ~Node();

	GridSquare* GetSquare();
	void SetSquare(GridSquare* square);
	bool IsOpen();
	int GetDistance();
	void SetDistance(int newDist);

	int GetX();
	int GetY();

protected:
	int m_x;
	int m_y;
	GridSquare* m_square;
	int m_distance;
};

#endif
