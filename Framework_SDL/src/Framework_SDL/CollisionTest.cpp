#include "CollisionTest.h"

CollisionTest::CollisionTest() {
	mTimer = Timer::Instance();

	mInputManager = InputManager::Instance();

	mGraphics = Graphics::Instance();

	mPlayer = new Player();
	mPlayer->Pos(Vector2(64, 64));

	mObstacle = new Obstacle();
	mObstacle->Pos(Vector2(Graphics::SCREEN_WIDTH / 2.0f, Graphics::SCREEN_HEIGHT / 2.0f));
}

void CollisionTest::EarlyUpdate() {
	//INPUT HANDLE
	mTimer->Reset();
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			mMouseCoords.x = event.motion.x;
			mMouseCoords.y = event.motion.y;
			break;
		}
	}
	mInputManager->Update();
}

void CollisionTest::Update() {
	//OBJECT UPDATES
	mPlayer->Update();
	mObstacle->Update();
}

void CollisionTest::LateUpdate() {
	//COLLISION DETECTION


	mInputManager->UpdatePreviousInput();
}

void CollisionTest::Render() {
	mGraphics->Clear();
	//RENDER 
	mPlayer->Render();
	mObstacle->Render();

	mGraphics->Render();
}

CollisionTest::~CollisionTest() {
	delete mPlayer;
	mPlayer = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	Timer::Release();
	mTimer = nullptr;

	
}
