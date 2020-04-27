#include "Player.h"

Player::Player() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mAnimating = false;

	mScores = 0;
	mLives = 3;

	mTexture = new Texture("Player.png", 0, 0, 64, 64);
	mTexture->Parent(this);
	mTexture->Pos(Vector2(64, 64));

	mSpeed = 200;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet();
	}
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
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Pos());
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
}