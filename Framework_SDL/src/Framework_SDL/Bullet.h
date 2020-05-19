#ifndef _BULLET_H
#define _BULLET_H
#include "PhysObject.h"
#include "Timer.h"
#include "PhysicsManager.h"

class Bullet : public PhysObject {

private:
	const int OFFSCREEN_BUFFER = 10;
	
	Timer* mTimer;
	
	float mSpeed;


	Texture* mTexture;
	Vector2 mDirection;

public:
	Bullet(bool friendly);
	~Bullet();

	void Fire(Vector2 pos, Vector2 direction);
	void Reload();
	
	void Hit(PhysObject* other) override;

	void Update();
	void Render();
private:
	bool IgnoreCollisions() override;
};

#endif


