#include "CollisionTest.h"

CollisionTest::CollisionTest() {

	mGraphics = Graphics::Instance();
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mPhysicsManager = PhysicsManager::Instance();
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, PhysicsManager::CollisionFlags::Hostile); //Friendly collides with hostile
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectiles, PhysicsManager::CollisionFlags::Hostile); //Friendly projectiles  collides with hostile 
	mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile, PhysicsManager::CollisionFlags::Friendly | PhysicsManager::CollisionFlags::FriendlyProjectiles);//Hostile collides with friendly projectiles and friendly 
	//mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectiles, PhysicsManager::CollisionFlags::Friendly);//Hostile projectiles  collides with friendly 
	


	mPlayer = new Player();
	mPlayer->Pos(Vector2(100, (Graphics::SCREEN_HEIGHT / 2) ));

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
	if (mInputManager->KeyPressed(SDL_SCANCODE_ESCAPE)) {
		mSceneState = SceneState::EXIT;
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
	mPhysicsManager->Update();
	
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

	PhysicsManager::Release();
	mPhysicsManager = nullptr;

	Timer::Release();
	mTimer = nullptr;

	
}
