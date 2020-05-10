#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Texture.h"
#include"PhysObject.h"
#include "Timer.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

class Obstacle : public PhysObject {

private:
	Timer* mTimer;
	Texture* mTexture;

	int mLives;
public:
	Obstacle();
	~Obstacle();

	bool IgnoreCollisions() override;

	void Hit(PhysObject* other) override;

	void Update();
	void Render();

};

#endif // !OBSTACLE_H
