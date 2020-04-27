#include "Graph.h"


inline bool operator<(const acumulativeNode & mine, const acumulativeNode & other)
{
	return mine.acumulatedCost > other.acumulatedCost;
}

Graph::Graph(std::vector<std::vector<node>> *terrain) {
	
	for (int i = 0; i < terrain->size(); ++i) {
		std::vector<node>aux;
		for (int j = 0; j < terrain->at(i).size(); ++j) {
			aux.push_back(terrain->at(i).at(j));

		}

		grid.push_back(aux);
	}

	updateEdges();
}

void Graph::updateEdges() {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid.at(i).size(); ++j) {

			if (grid.at(i).at(j).value == 1) {

				//COMPROBAR QUE LA I NO ES 0
				if (i != 0 && grid.at(i - 1).at(j).value == 1 && grid.at(i-1).at(j).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i - 1).at(j), 1 });
				}

				if (j != 0 && grid.at(i).at(j - 1).value == 1 && grid.at(i).at(j-1).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i).at(j - 1), 1 });
				}

				if (j != grid.at(i).size() - 1 && grid.at(i).at(j + 1).value == 1 && grid.at(i).at(j+1).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i).at(j + 1), 1 });
				}

				if (i != grid.size() - 1 && grid.at(i + 1).at(j).value == 1&& grid.at(i+1).at(j).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i + 1).at(j), 1 });
				}

				//COMPROBAR QUE LA J NO ES 0
				if (i != 0 && j != grid.at(i).size() - 1 && grid.at(i - 1).at(j + 1).value == 1 && grid.at(i-1).at(j+1).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i - 1).at(j + 1), 2 });
				}

				if (i != 0 && j != 0 && grid.at(i - 1).at(j - 1).value == 1&& grid.at(i-1).at(j-1).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i - 1).at(j - 1), 2 });
				}

				if (i != grid.size() - 1 && j != 0 && grid.at(i + 1).at(j - 1).value == 1 && grid.at(i+1).at(j-1).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i + 1).at(j - 1), 2 });
				}

				if (j != grid.at(i).size() - 1 && i != grid.size() - 1 && grid.at(i + 1).at(j + 1).value == 1 && grid.at(i+1).at(j+1).value == 1) {
					grid.at(i).at(j).connections.push_back({ &grid.at(i).at(j), &grid.at(i + 1).at(j + 1), 2 });
				}
			}
		}
	}
}

node Graph::getNodeAt(int x, int y)
{
	return grid.at(x).at(y);
}

node * Graph::getNodeRefAt(int x, int y)
{
	return &grid.at(x).at(y);
}

void Graph::setNode(Vector2 nodePos, int nodeVal)
{
	grid.at(nodePos.y).at(nodePos.x).value = nodeVal;
}

std::vector<std::vector<node>> Graph::getGrid(){
	return grid;
}


Graph::Graph()
{
}

Graph::~Graph()
{
}

