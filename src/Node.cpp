
#include "Node.h"
#include "Level.h"
#include <math.h>

bool NodesByDistance(Node* a, Node* b) {
	return a->GetDistance() < b->GetDistance();
}

bool NodesByScore(Node* a, Node* b) {
	return a->GetScore() < b->GetScore();
}

Node::Node(int x, int y) : 
	m_x(x), m_y(y), m_square(NULL), m_distance(NODE_INFINITY), m_heuristic(0) {
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

void Node::CalculateHeuristic(int dx, int dy) {
	m_heuristic = dx + dy;
}

int Node::GetHeuristic() {
	return m_heuristic;
}

int Node::GetScore() {
	return m_heuristic + m_distance;
}
