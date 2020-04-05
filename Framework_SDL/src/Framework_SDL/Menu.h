#ifndef _MENU_H
#define _MENU_H
#include "SceneManager.h"
#include "Scoreboard.h"

class Menu : public SceneManager {
private:
	

	Vector2 mMouseCoords;
	bool clicked;
	InputManager* mInputManager;

	Timer* mTimer;

	Graphics* mGraphics;

	Texture* mBackground;


	Texture* playButton;
	Texture* exitButton;

	Scoreboard* mScoreTest;

public:
	void EarlyUpdate()override;
	void Update()override;
	void LateUpdate()override;
	void Render()override;

	Menu();
	~Menu();

};

#endif 

