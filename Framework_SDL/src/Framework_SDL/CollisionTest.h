#ifndef _COLLISIONTEST_H
#define  _COLLISIONTEST_H
#include "SceneManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "PhysicsManager.h"

class CollisionTest : public SceneManager {
private:
	Vector2 mMouseCoords;

	Graphics* mGraphics;

	InputManager* mInputManager;
	PhysicsManager* mPhysicsManager;

	Timer* mTimer;

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