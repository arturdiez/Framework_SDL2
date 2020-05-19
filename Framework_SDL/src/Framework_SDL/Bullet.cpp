#include "Bullet.h"
#include "BoxCollider.h"

Bullet::Bullet(bool friendly) {
	mTimer = Timer::Instance();

	mSpeed = 1000.0f;


	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);
	Name("Bullet");

	//Rotate(45);
	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	if (friendly) {
		PhysicsManager::Instance()->RegisterObject(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);

	}
	else {
		PhysicsManager::Instance()->RegisterObject(this, PhysicsManager::CollisionLayers::HostileProjectiles);
	}
}

Bullet::~Bullet() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

bool Bullet::IgnoreCollisions() {
	return !Active();
}

void Bullet::Fire(Vector2 pos, Vector2 direction) {
	Pos(pos);
	mDirection = direction;
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Hit(PhysObject* other) {

	Reload();
	std::cout << "Object : "<< other->Name() << " HIT\n";
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