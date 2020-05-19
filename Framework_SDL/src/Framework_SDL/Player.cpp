#include "Player.h"

Player::Player() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mAnimating = false;
	mWasHit = false;

	
	mScores = 0;
	mLives = 3;

	mTexture = new Texture("Player.png", 0, 0, 64, 64);
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);
	Name("Player");

	mSpeed = 200;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	PhysicsManager::Instance()->RegisterObject(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;

	delete mTexture;
	mTexture = nullptr;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}


bool Player::IgnoreCollisions() {
	return mLives <= 0;
}


void Player::Hit(PhysObject* other) {
	mWasHit = true;
	std::cout << "Object : " << Name() << " HIT\n";
}

bool Player::WasHit() {
	
	return mWasHit;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScores;
}

int Player::Lives() {
	return mLives;
}

void Player::HandleMovement() {

	if (mInput->KeyDown(SDL_SCANCODE_W)) {
		Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime(), world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_S)) {
		Translate(VEC2_UP * mSpeed * mTimer->DeltaTime(), world);
	}
	if (mInput->KeyDown(SDL_SCANCODE_A)) {
		Translate(-VEC2_RIGHT * mSpeed * mTimer->DeltaTime(), world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_D)) {
		Translate(VEC2_RIGHT * mSpeed * mTimer->DeltaTime(), world);
	}
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Vector2(Pos().x, Pos().y - mTexture->ScaledDimensions().y / 2.0f), -VEC2_UP);
				break;
			}
		}
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Vector2(Pos().x, Pos().y + mTexture->ScaledDimensions().y/2.0f), VEC2_UP);
				break;
			}
		}
	}
	if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Vector2(Pos().x - mTexture->ScaledDimensions().x / 2.0f, Pos().y), -VEC2_RIGHT);
				break;
			}
		}
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Vector2(Pos().x + mTexture->ScaledDimensions().x / 2.0f, Pos().y), VEC2_RIGHT);
				break;
			}
		}
	}
}

void Player::Update() {
	if (Active()) {
		HandleMovement();
		HandleFiring();
	}

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
		mTexture->Render();

		for (int i = 0; i < MAX_BULLETS; ++i) {
			mBullets[i]->Render();
		}
		PhysObject::Render();
}