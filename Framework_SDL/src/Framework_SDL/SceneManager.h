#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
#include "Sprite.h"
#include "InputManager.h"
#include "AudioManager.h"

class SceneManager {
private:
	static SceneManager* sInstance;

public:
	enum SceneState {RUNNING, GOTO_PLAY, GOTO_COLLISION, EXIT};
	SceneState getSceneState();
	SceneState mSceneState;

	static SceneManager* Instance();
	static void Release();
	
	virtual void EarlyUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();



	/*SDL_Event mEvents;
	InputManager* mInputManager;
	AudioManager* mAudioManager;
	AssetManager* mAssetManager;

	Timer* mTimer;
	Graphics* mGraphics;
	Texture* mFont;
	static void release();
	
	GameManager::~GameManager() {
	AudioManager::Release();
	mAudioManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	Timer::Release();
	mTimer = nullptr;

	delete mFont;
	mFont = nullptr;
}
	*/


	SceneManager();
	~SceneManager();

	

};
#endif 

