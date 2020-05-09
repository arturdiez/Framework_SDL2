#ifndef _BULLET_H
#define _BULLET_H
#include "PhysObject.h"
#include "Timer.h"

class Bullet : public PhysObject {

private:
	const int OFFSCREEN_BUFFER = 10;
	
	Timer* mTimer;
	
	float mSpeed;

	Texture* mTexture;
	Vector2 mDirection;

public:
	Bullet();
	~Bullet();

	void Fire(Vector2 pos, Vector2 direction);
	void Reload();

	void Update();
	void Render();
};

#endif


