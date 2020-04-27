#include "SteeringBehavior.h"
using namespace std;


inline bool operator<(const acumulativeNode & mine, const acumulativeNode & other)
{
	return mine.acumulatedCost > other.acumulatedCost;
}

SteeringBehavior::SteeringBehavior()
{
}

SteeringBehavior::~SteeringBehavior()
{
}

Vector2 SteeringBehavior::Seek(Agent *agent, Vector2 target, float dtime)
{
	Vector2 desired_velocity = target - agent->position;
	desired_velocity.Normalized();
	desired_velocity *= agent->max_velocity;

	Vector2 steering_force = desired_velocity - agent->velocity;
	steering_force /= agent->max_velocity;
	steering_force = steering_force * agent->max_force;

	return steering_force;
}

Vector2 SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2 SteeringBehavior::Arrive(Agent *agent, Vector2 target, int slow_radius, float dtime)
{
	float slow_factor = (target - agent->position).Magnitude() / slow_radius;

	Vector2 desired_velocity = target - agent->position;
	desired_velocity.Normalized();
	if ((target - agent->position).Magnitude() > slow_radius)
		desired_velocity *= agent->max_velocity;
	else
		desired_velocity *= agent->max_velocity * slow_factor;

	Vector2 steering_force = desired_velocity - agent->velocity;
	//steering_force /= agent->max_velocity;
	//steering_force = steering_force * agent->max_force;

	return steering_force;
}

Vector2 SteeringBehavior::Arrive(Agent *agent, Agent *target, int slow_radius, float dtime)
{
	return Arrive(agent, target->position, slow_radius, dtime);
}

Vector2 SteeringBehavior::SimplePathFollowing(Agent *agent, float dtime)
{
	//There is a path and we have not started to follow it
	if ((agent->currentTargetIndex == -1) && (agent->path.points.size()>0))
		agent->setCurrentTargetIndex(0); 

	//We are in the middle of a path
	if (agent->getCurrentTargetIndex() >= 0)
	{
		float dist = Distance(agent->getPosition(), agent->path.points[agent->currentTargetIndex]);
		// We 've reached the current target
		if (dist < agent->path.ARRIVAL_DISTANCE)
		{
			// Current target is path's last point?
			if (agent->getCurrentTargetIndex() == agent->path.points.size() - 1)
			{
				if (dist < 3) // We've reached the end of the path
				{
					agent->path.points.clear();
					agent->setCurrentTargetIndex(-1);
					agent->setVelocity(Vector2(0, 0));
					return Vector2(0,0);
				}
				else
				{
					return Arrive(agent, agent->getTarget(), agent->path.ARRIVAL_DISTANCE, dtime);
				}
			}
			// Go to the next point in the path
			agent->setCurrentTargetIndex(agent->currentTargetIndex+1);
		}
		// Seek to current target
		agent->setTarget(agent->path.points[agent->currentTargetIndex]);
		return Seek(agent, agent->getTarget(), dtime);
	}
	// Do nothing if there is no path!
	return Vector2(0, 0);  
}

std::pair<std::vector<Vector2>,int> SteeringBehavior::BreadthFirstSearch(Vector2 agentCoord, Vector2 targetCoord, Graph *terrain, float dtime)
{
	std::queue<node*> frontier;
	std::map<node*, node*> parentMap;


	frontier.push(terrain->getNodeRefAt(agentCoord.x, agentCoord.y));
	parentMap[frontier.front()] = nullptr; //root has no parent

	node* destinationNode=nullptr;

	while (!frontier.empty()) {
		for (edge e : frontier.front()->connections) {
			//std::cout << "frontier node: " << frontier.front() << std::endl;
			//std::cout <<  "connection node:\n\torigin: " << e.origin << "\n\tdestination: " << e.destination << std::endl;
			if (e.origin == frontier.front()) { //comprobamos solo las conexiones que tienen como origen el nodo de la frontera
				
				std::map<node*, node*>::iterator it = parentMap.find(e.destination);

				if (it == parentMap.end()) {//solo visitamos los nodos que no tienen padre, es decir que no han sido visitados
					if (e.destination->value == 2) {
						parentMap[e.destination] = e.origin;
						destinationNode = e.destination;
						terrain->setNode({e.destination->cellWorldLocation}, 1);
						goto makeAnsVec;
					}
					frontier.push(e.destination);
					parentMap[e.destination] = e.origin;
				}
			}
		}
		frontier.pop();
	}

makeAnsVec:
	std::vector<Vector2> ans;
	std::pair<std::vector<Vector2>,int> pair;
	ans.push_back(destinationNode->cellWorldLocation);
	node* aux = destinationNode;
	while (aux!=nullptr) {
		Vector2 aux2;
		if (parentMap[aux] == nullptr)
			break;

		aux2 = parentMap[aux]->cellWorldLocation;
		ans.push_back(aux2);
		aux = parentMap[aux];
		
		
	}

	pair.first = ans;
	pair.second = parentMap.size();

	return pair;
}

std::pair<std::vector<Vector2>, int> SteeringBehavior::Dijkstra(Vector2 agentCoord, Vector2 targetCoord, Graph * terrain, float dtime)
{	
	std::priority_queue<acumulativeNode> frontier;
	std::map<node*, node*> parentMap;
	std::map<node*, int>cost_so_far;

	frontier.push({ terrain->getNodeRefAt(agentCoord.x, agentCoord.y),0});
	parentMap[frontier.top().node] = nullptr; //root has no parent
	cost_so_far[frontier.top().node] = 0; //root has no cost

	node* destinationNode = nullptr;

	while (!frontier.empty()) {
		for (edge e : frontier.top().node->connections) {
			
			float localCost = 0;
			localCost = frontier.top().acumulatedCost + e.cost;

			if ((cost_so_far[e.destination] > localCost || cost_so_far[e.destination] == 0) && (e.destination->cellWorldLocation != Vector2{agentCoord.y, agentCoord.x})) {
								
				cost_so_far[e.destination] = localCost;
				frontier.push({ e.destination, localCost });
				parentMap[e.destination] = e.origin;
			}

			if (e.destination->value == 2) {
				//hemos llegado al destino						
				destinationNode = e.destination;
				terrain->setNode(e.destination->cellWorldLocation, 1);
				goto makeAnsVec;
			}
		}
		frontier.pop();
	}
	
makeAnsVec:
	std::vector<Vector2> ans;
	std::pair<std::vector<Vector2>, int> pair;
	ans.push_back(destinationNode->cellWorldLocation);
	node* aux = destinationNode;
	while (aux != nullptr) {
		Vector2 aux2;
		if (parentMap[aux] == nullptr)
			break;

		aux2 = parentMap[aux]->cellWorldLocation;
		ans.push_back(aux2);
		aux = parentMap[aux];

	}
	pair.first = ans;
	pair.second = parentMap.size();

	return pair;
}

float ManhattanDist(Vector2 origin, Vector2 destiny) {
	return{abs(destiny.x-origin.x)+abs(destiny.y-origin.y)};
}

std::pair<std::vector<Vector2>, int> SteeringBehavior::GBFS(Vector2 agentCoord, Vector2 targetCoord, Graph * terrain, float dtime)
{
	std::priority_queue<acumulativeNode> frontier;
	std::map<node*, node*> parentMap;
	std::map<node*, int>costMap;


	frontier.push({ terrain->getNodeRefAt(agentCoord.x, agentCoord.y),0 });
	parentMap[frontier.top().node] = nullptr; //root has no parent
	costMap[frontier.top().node] = ManhattanDist(agentCoord, targetCoord); //root has no cost

	node* destinationNode = nullptr;
	bool firstIter = true;


	while (!frontier.empty()) {
		bool canBeExpanded = false;
		for (edge e : frontier.top().node->connections) {

			std::map<node*, node*>::iterator it = parentMap.find(e.destination); 

			if (it==parentMap.end()) { //si el nodo que estamos mirando no ha sido ya visitado
				
				float heuristicVal = ManhattanDist({ e.destination->cellWorldLocation.x, e.destination->cellWorldLocation.y }, { targetCoord.x, targetCoord.y });
				costMap[e.destination] = heuristicVal;
				frontier.push({ e.destination, heuristicVal });
				parentMap[e.destination] = e.origin;
				canBeExpanded = true;
			}

			if (e.destination->value == 2) {
				//hemos llegado al destino						
				destinationNode = e.destination;
				terrain->setNode(e.destination->cellWorldLocation, 1);
				goto makeAnsVec;
			}
		}

		if (!canBeExpanded)
			frontier.pop();

		if (firstIter) {
			frontier.pop();
			firstIter = false;
		}
	}


makeAnsVec:
	std::vector<Vector2> ans;
	std::pair<std::vector<Vector2>, int> pair;
	ans.push_back(destinationNode->cellWorldLocation);
	node* aux = destinationNode;
	while (aux != nullptr) {
		Vector2 aux2;
		if (parentMap[aux] == nullptr)
			break;

		aux2 = parentMap[aux]->cellWorldLocation;
		ans.push_back(aux2);
		aux = parentMap[aux];

	}
	pair.first = ans;
	pair.second = parentMap.size();

	return pair;
}

std::pair<std::vector<Vector2>, int> SteeringBehavior::AStar(Vector2 agentCoord, Vector2 targetCoord, Graph * terrain, float dtime)
{
	std::priority_queue<acumulativeNode> frontier;
	std::map<node*, node*> parentMap;
	std::map<node*, int>costMap;


	frontier.push({ terrain->getNodeRefAt(agentCoord.x, agentCoord.y),0 });
	parentMap[frontier.top().node] = nullptr; //root has no parent
	costMap[frontier.top().node] = ManhattanDist(agentCoord, targetCoord); //root has no cost

	node* destinationNode = nullptr;
	bool firstIter = true;


	while (!frontier.empty()) {
		bool canBeExpanded = false;
		for (edge e : frontier.top().node->connections) {

			std::map<node*, node*>::iterator it = parentMap.find(e.destination);

			if (it == parentMap.end()) { //si el nodo que estamos mirando no ha sido ya visitado

				int heuristicVal = ManhattanDist(e.destination->cellWorldLocation, targetCoord);
				int acumulatedCost = frontier.top().acumulatedCost + e.cost;

				float formulaVal = heuristicVal * 1 + acumulatedCost * 1.1f;
				costMap[e.destination] = formulaVal;
				frontier.push({ e.destination, formulaVal });
				parentMap[e.destination] = e.origin;
				canBeExpanded = true;
			}

			if (e.destination->value == 2) {
				//hemos llegado al destino						
				destinationNode = e.destination;
				terrain->setNode(e.destination->cellWorldLocation, 1);
				goto makeAnsVec;
			}
		}

		if (!canBeExpanded)
			frontier.pop();

		if (firstIter) {
			frontier.pop();
			firstIter = false;
		}
	}


makeAnsVec:
	std::vector<Vector2> ans;
	std::pair<std::vector<Vector2>, int>pair;
	ans.push_back(destinationNode->cellWorldLocation);
	node* aux = destinationNode;
	while (aux != nullptr) {
		Vector2 aux2;
		if (parentMap[aux] == nullptr)
			break;

		aux2 = parentMap[aux]->cellWorldLocation;
		ans.push_back(aux2);
		aux = parentMap[aux];

	}
	pair.first = ans;
	pair.second = parentMap.size();

	return pair;
}


std::pair<std::vector<Vector2>, int> SteeringBehavior::AStarMultiNode(Vector2 agentCoord, Vector2 targetCoord, Graph * terrain, float dtime)
{
	std::priority_queue<acumulativeNode> frontier;
	std::map<node*, node*> parentMap;
	std::map<node*, int>costMap;


	frontier.push({ terrain->getNodeRefAt(agentCoord.x, agentCoord.y),0 });
	parentMap[frontier.top().node] = nullptr; //root has no parent
	costMap[frontier.top().node] = ManhattanDist(agentCoord, targetCoord); //root has no cost

	node* destinationNode = nullptr;
	bool firstIter = true;


	while (!frontier.empty()) {
		bool canBeExpanded = false;
		for (edge e : frontier.top().node->connections) {

			std::map<node*, node*>::iterator it = parentMap.find(e.destination);

			if (it == parentMap.end()) { //si el nodo que estamos mirando no ha sido ya visitado

				int heuristicVal = ManhattanDist(e.destination->cellWorldLocation, targetCoord);
				int acumulatedCost = frontier.top().acumulatedCost + e.cost;
				
				float formulaVal = heuristicVal * 1 + acumulatedCost * 1.85f;
				costMap[e.destination] = formulaVal;
				frontier.push({ e.destination, formulaVal });
				parentMap[e.destination] = e.origin;
				canBeExpanded = true;
			}

			if (e.destination->value == 2 && e.destination->cellWorldLocation == Vector2{targetCoord.y, targetCoord.x}) {
				//hemos llegado al destino						
				destinationNode = e.destination;
				terrain->setNode(e.destination->cellWorldLocation, 1);
				goto makeAnsVec;
			}
		}

		if (!canBeExpanded)
			frontier.pop();

		if (firstIter) {
			frontier.pop();
			firstIter = false;
		}
	}


makeAnsVec:
	std::vector<Vector2> ans;
	std::pair<std::vector<Vector2>, int>pair;
	ans.push_back(destinationNode->cellWorldLocation);
	node* aux = destinationNode;
	while (aux != nullptr) {
		Vector2 aux2;
		if (parentMap[aux] == nullptr)
			break;

		aux2 = parentMap[aux]->cellWorldLocation;
		ans.push_back(aux2);
		aux = parentMap[aux];

	}
	pair.first = ans;
	pair.second = parentMap.size();

	return pair;
}
