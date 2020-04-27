#pragma once
#include"Math.h"
#include <string>

struct node;

struct edge {
	node* origin;
	node* destination;
	int cost;
};

struct node {
	int value;
	std::vector<edge> connections;
	Vector2 cellWorldLocation;
};


struct acumulativeNode {
	node* node;
	float acumulatedCost;
};


inline bool operator<(const acumulativeNode &mine, const acumulativeNode  &other);

std::ostream &operator<<(std::ostream &os, node const &m);

inline bool operator==(const node & mine, const int & other);

class Graph {
public:
	Graph(std::vector<std::vector<node>> *terrain);
	Graph();
	~Graph();

	void updateEdges();
	node getNodeAt(int x, int y);
	node* getNodeRefAt(int x, int y);
	void setNode(Vector2 nodePos, int nodeVal);

	std::vector<std::vector<node>> getGrid();

private:
	std::vector<std::vector<node>> grid;
};
