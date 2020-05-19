#ifndef _PLAYER_H
#define _PLAYER_H
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "BoxCollider.h"
#include"PhysicsManager.h"

class Player : public PhysObject {
private:
	Timer* mTimer;
	InputManager* mInput;

	bool mAnimating;
	bool mWasHit;

	int mScores;
	int mLives;

	Texture* mTexture;

	float mSpeed;

	static const int MAX_BULLETS = 50;
	Bullet* mBullets[MAX_BULLETS];
	
private:

	bool IgnoreCollisions() override;

	void HandleMovement();
	void HandleFiring();
public:
	Player();
	~Player();

	bool IsAnimating();

	void Hit(PhysObject* other) override;
	bool WasHit();

	int Score();
	int Lives();

	void Update();
	void Render();
};


#endif 

