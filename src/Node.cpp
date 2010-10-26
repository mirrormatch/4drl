
#include "Node.h"
#include "Level.h"
#include <math.h>

bool NodesByDistance(Node* a, Node* b) {
	return a->GetDistance() < b->GetDistance();
}

Node::Node(int x, int y) : 
	m_x(x), m_y(y), m_square(NULL), m_distance(NODE_INFINITY) {
}

Node::~Node() {
}

GridSquare* Node::GetSquare() {
	return m_square;
}

void Node::SetSquare(GridSquare* square) {
	m_square = square;
}

bool Node::IsOpen() {
	if(m_square) {
		return (m_square->entity == NULL);
	}
	return true;
}

int Node::GetDistance() {
	return m_distance;
}

void Node::SetDistance(int newDist) {
	m_distance = newDist;
}

int Node::GetX() {
	return m_x;
}

int Node::GetY() {
	return m_y;
}
