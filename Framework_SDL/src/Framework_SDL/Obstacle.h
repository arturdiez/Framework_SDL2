#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Texture.h"
#include"PhysObject.h"
#include "Timer.h"
#include "BoxCollider.h"

class Obstacle : public PhysObject {

private:
	Timer* mTimer;
	Texture* mTexture;
public:
	Obstacle();
	~Obstacle();

	void Update();
	void Render();

};

#endif // !OBSTACLE_H
