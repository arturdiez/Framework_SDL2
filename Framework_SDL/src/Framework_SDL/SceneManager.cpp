#include "SceneManager.h"

SceneManager* SceneManager::sInstance = nullptr;

SceneManager* SceneManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new SceneManager();
	}
	return sInstance;
}

void SceneManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

SceneManager::SceneManager() {
	mSceneState = SceneState::RUNNING;
}

SceneManager::SceneState SceneManager::getSceneState() {
	return mSceneState;
}

SceneManager::~SceneManager() {

}

void SceneManager::EarlyUpdate() {}
void SceneManager::Update() {}
void SceneManager::LateUpdate() {}
void SceneManager::Render() {}