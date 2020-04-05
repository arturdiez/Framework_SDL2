#include "Play.h"

Play::Play() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mGraphics = Graphics::Instance();

	mPlayer = new Player();

	//Room = new GameObject(Vector2(Graphics::Instance()->SCREEN_WIDTH/2,Graphics::Instance()->SCREEN_HEIGHT/2));
	//
	//for (int i = 0; i < 10; ++i) {
	//	for (int j = 0; j < 10; ++j) {
	//		tiles[i][j] = new Texture("tile.png");
	//		tiles[i][j]->Parent(Room);
	//		tiles[i][j]->Pos(Vector2(64 * i + 32, 64 * j + 32));
	//	}
	//}
	//Room->Pos(Vector2(200,200));

	tiles[0][0] = new Texture("tile.png");
	tiles[0][0]->Pos(Vector2(400,300));
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
}


void Play::EarlyUpdate() {
	mInputManager->Update();
	
}
void Play::Update() {

	SDL_Event event;
	SDL_PollEvent(&event);

	mPlayer->Update();
}
void Play::LateUpdate() {
	mInputManager->UpdatePreviousInput();
	mTimer->Reset();
}

void Play::Render() {
	mGraphics->Clear();

	mPlayer->Render();

	tiles[0][0]->Render();
	
	mGraphics->Render();
}