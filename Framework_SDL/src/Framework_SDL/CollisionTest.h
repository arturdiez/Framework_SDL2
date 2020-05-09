#ifndef _COLLISIONTEST_H
#define  _COLLISIONTEST_H
#include "SceneManager.h"
#include "Player.h"
#include "Obstacle.h"

class CollisionTest : public SceneManager {
private:
	Vector2 mMouseCoords;
	InputManager* mInputManager;

	Timer* mTimer;

	Graphics* mGraphics;

	Player* mPlayer;
	Obstacle* mObstacle;
	
public:
	void EarlyUpdate()override;
	void Update()override;
	void LateUpdate()override;
	void Render()override;

	CollisionTest();
	~CollisionTest();
};
#endif 