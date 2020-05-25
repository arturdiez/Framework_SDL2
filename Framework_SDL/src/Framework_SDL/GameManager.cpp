#include "GameManager.h"
#include "Menu.h"
#include "Play.h"
#include "CollisionTest.h"

GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new GameManager();
	}
	return sInstance;
}

void GameManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

GameManager::GameManager() {
	mGameState = GameState::MENU;
	mCurrentScene = new Menu();
	mTimer = Timer::Instance();
}

GameManager::~GameManager() {
	SceneManager::Release();
	mCurrentScene = nullptr;
	Timer::Release();
	mTimer = nullptr;
}

void GameManager::Run() {
	while (mGameState != GameState::EXIT) 
	{
		mTimer->Update();

		switch (mCurrentScene->getSceneState())
		{
		case SceneManager::SceneState::RUNNING:
			if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {
				mCurrentScene->EarlyUpdate();
				mCurrentScene->Update();
				mCurrentScene->LateUpdate();
				mCurrentScene->Render();
		}
			break;
		case SceneManager::SceneState::EXIT:
			switch (mGameState)
			{
			case GameState::MENU:
				delete mCurrentScene;
				mCurrentScene = nullptr;
				mGameState = GameState::EXIT;
				break;
			case GameState::PLAY:
				delete mCurrentScene;
				mCurrentScene = new Menu();
				mGameState = GameState::MENU;
				break;
			case GameState::COLLISIONTEST:
				delete mCurrentScene;
				mCurrentScene = new Menu();
				mGameState = GameState::MENU;
				break;
			}
			break;
		case SceneManager::SceneState::GOTO_PLAY:
			switch (mGameState)
			{
			case GameState::MENU:
				delete mCurrentScene;
				mCurrentScene = new Play();
				mGameState = GameState::PLAY;
				break;
			}
			break;
		case SceneManager::SceneState::GOTO_COLLISION:
			switch (mGameState)
			{
			case GameState::MENU:
				delete mCurrentScene;
				mCurrentScene = new CollisionTest();
				mGameState = GameState::COLLISIONTEST;
				break;
			}
			break;
		}
	}
}