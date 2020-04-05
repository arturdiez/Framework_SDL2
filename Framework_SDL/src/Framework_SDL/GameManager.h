#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H


#include "SceneManager.h"

class GameManager {
private:
	const int FRAME_RATE = 60;
	static GameManager* sInstance;
public:
	static GameManager* Instance();
	static void Release();
	
	enum GameState {MENU, PLAY, EXIT};
	GameState mGameState;
	SceneManager* mCurrentScene;

	Timer* mTimer;

	//Runs the game
	void Run();
	
	GameManager();
	~GameManager();
};

#endif 
