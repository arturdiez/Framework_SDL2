#include "Bullet.h"
#include "BoxCollider.h"

Bullet::Bullet() {
	mTimer = Timer::Instance();

	mSpeed = 1000.0f;

	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	//Rotate(45);
	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
}

Bullet::~Bullet() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Bullet::Fire(Vector2 pos, Vector2 direction) {
	Pos(pos);
	mDirection = direction;
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Update() {
	if (Active()) {
		Translate(mDirection * mSpeed * mTimer->DeltaTime(), local);
		Vector2 pos = Pos();

		if (pos.x < OFFSCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFFSCREEN_BUFFER || pos.y < OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER) {
			Reload();
		}
	
	}
}

void Bullet::Render() {
	if (Active()) {
		mTexture->Render();
		PhysObject::Render();
	}
		
}