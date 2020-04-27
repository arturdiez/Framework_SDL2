#include "Play.h"

Play::Play() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mGraphics = Graphics::Instance();

	mPlayer = new Player();

	mAgent = new Agent();
	mAgent->setTarget(Vector2(-20, -20));
	agents.push_back(mAgent);

	coinText = new Texture("coin.png", 0, 0, 32, 32);
	tileText = new Texture("Tile.png", 0, 0, 32, 32);
	
	pathfindingInCourse = false;

	iterations = 0;
	visitedNodes = 0;
	maxIterations = 8;
	min = 0;
	max = 0;
	once = false;

	num_cell_x = Graphics::SCREEN_WIDTH / Graphics::CELL_SIZE;
	num_cell_y = Graphics::SCREEN_HEIGHT / Graphics::CELL_SIZE;
	
	setMap();

	// set agent position coords to the center of a random cell
	Vector2 rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2(-1, -1);
	while ((!isValidCell(coinPosition)) || (Distance(coinPosition, rand_cell) < 3)) {
		coinPosition = Vector2((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
		agents[0]->setTarget(coinPosition);
	}

	map->getNodeRefAt(coinPosition.y, coinPosition.x)->value = 2;

	

}

Play::~Play() {
	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	Timer::Release();
	mTimer = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
		agents[i] = nullptr;
	}

	delete tileText;
	tileText = nullptr;

}

void Play::setMap() {
	std::vector < std::vector<node>> aux;

	for (int i = 0; i < terrain.size(); ++i) {
		std::vector<node> aux2;
		for (int j = 0; j < terrain.at(i).size(); ++j) {
			node aux3;
			aux3.value = terrain.at(i).at(j);
			aux3.cellWorldLocation = Vector2(j, i);
			aux2.push_back(aux3);
		}
		aux.push_back(aux2);
	}

	map = new Graph(&aux);
}

void Play::EarlyUpdate() {
	mTimer->Reset();
	mInputManager->Update();

}
void Play::Update() {

	SDL_Event event;
	SDL_PollEvent(&event);

	mPlayer->Update();

	if ((agents[0]->getCurrentTargetIndex() == -1) && (pix2cell(agents[0]->getPosition()) == coinPosition))
	{


		coinPosition = Vector2(-1, -1);
		while ((!isValidCell(coinPosition)) || (Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3))
			coinPosition = Vector2((float)(rand() % num_cell_y), (float)(rand() % num_cell_x));

		//agents[0]->setTarget(coinPosition);
		map->getNodeRefAt(coinPosition.y, coinPosition.x)->value = 2;
		pathfindingInCourse = false;
		iterations++;


	}

	Vector2 inverCoin{ coinPosition.x, coinPosition.y };
	Vector2 inverAgent{ agents[0]->getPosition().y, agents[0]->getPosition().x };

	std::pair<std::vector<Vector2>, int> path;
	Vector2 agentCoord = pix2cell(inverAgent);

	if (pathfindingInCourse == false && iterations != maxIterations) {
		path = agents[0]->Behavior()->GBFS(pix2cell(inverAgent), inverCoin, map, mTimer->DeltaTime());
		numberOfNodes.push_back(path.second);
		visitedNodes += path.second;
		pathfindingInCourse = true;
	}

	for (std::vector<Vector2>::reverse_iterator i = path.first.rbegin(); i != path.first.rend(); ++i) {
		agents[0]->addPathPoint(cell2pix(*i));
	}

	Vector2 steering_force = agents[0]->Behavior()->SimplePathFollowing(agents[0], mTimer->DeltaTime());
	agents[0]->Update(steering_force, mTimer->DeltaTime());
}

void Play::LateUpdate() {
	mInputManager->UpdatePreviousInput();
}

void Play::Render() {
	mGraphics->Clear();

	
	
	drawMaze();
	drawCoin();
	mPlayer->Render();
	agents[0]->Render();

	mGraphics->Render();
}

void Play::drawMaze()
{
	
	Vector2 coords;
	for (int j = 0; j < num_cell_y; j++)
	{
		for (int i = 0; i < num_cell_x; i++)
		{
			switch (terrain[j][i])
			{
			case 0:
				tileText->Pos(Vector2(coords.x + Graphics::CELL_SIZE / 2, coords.y + Graphics::CELL_SIZE / 2));
				tileText->Render();
				break;
			case 1: // Do not draw if it is not necessary (bg is already black)
			default:
				continue;
			}

			coords = cell2pix(Vector2(i, j)) - Vector2((float)Graphics::CELL_SIZE/2, (float)Graphics::CELL_SIZE/2);

		}
	}
}

void Play::drawCoin()
{
	Vector2 coin_coords = cell2pix(coinPosition);
	int offset = Graphics::CELL_SIZE / 2;
	coinText->Pos(coin_coords);
	coinText->Render();
}

Vector2 Play::cell2pix(Vector2 cell)
{
	int offset = Graphics::CELL_SIZE / 2;
	return Vector2(cell.x*Graphics::CELL_SIZE + offset, cell.y* Graphics::CELL_SIZE + offset);
}

Vector2 Play::pix2cell(Vector2 pix)
{
	return Vector2((float)((int)pix.x / Graphics::CELL_SIZE), (float)((int)pix.y / Graphics::CELL_SIZE));
}

bool Play::isValidCell(Vector2 cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x] == 0);
}