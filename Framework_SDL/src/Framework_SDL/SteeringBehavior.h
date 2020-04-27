#pragma once
#include <vector>
#include "Agent.h"
#include "Math.h"
#include "Path.h"
#include "Graph.h"
#include <queue>
#include <map>


class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();

	Vector2 Seek(Agent *agent, Vector2 target, float dtime);
	Vector2 Seek(Agent *agent, Agent *target, float dtime);
	Vector2 Arrive(Agent *agent, Vector2 target, int slow_radius, float dtime);
	Vector2 Arrive(Agent *agent, Agent *target, int slow_radius, float dtime);
	Vector2 SimplePathFollowing(Agent *agent, float dtime);
	std::pair<std::vector<Vector2>, int> BreadthFirstSearch(Vector2 agentCoord, Vector2 targetCoord, Graph *terrain, float dtime);
	std::pair<std::vector<Vector2>, int> Dijkstra(Vector2 agentCoord, Vector2 targetCoord, Graph *terrain, float dtime);
	std::pair<std::vector<Vector2>, int> GBFS(Vector2 agentCoord, Vector2 targetCoord, Graph *terrain, float dtime);
	std::pair<std::vector<Vector2>, int> AStar(Vector2 agentCoord, Vector2 targetCoord, Graph *terrain, float dtime);
	std::pair<std::vector<Vector2>, int> AStarMultiNode(Vector2 agentCoord, Vector2 targetCoord, Graph *terrain, float dtime);

};