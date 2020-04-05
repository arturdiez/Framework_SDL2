#ifndef _PLAY_H
#define _PLAY_H
#include "SceneManager.h"
#include "Player.h"

class Play: public SceneManager {
private:
	Timer* mTimer;
	InputManager* mInputManager;
	Graphics* mGraphics;

	GameObject* Room;
	Texture* tiles[10][10];
	
	
	Player* mPlayer;

public:
	void EarlyUpdate()override;
	void Update()override;
	void LateUpdate()override;
	void Render()override;

	Play();
	~Play();
};

#endif 

