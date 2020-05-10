#include "Obstacle.h"
#include "Bullet.h"

Obstacle::Obstacle() {
	mTexture = new Texture("Tile.png", 0, 0, 32, 32);
	mTexture->Parent(this);
	mTexture->Scale(Vector2(2, 2));
	Name("Obstacle");


	mLives = 10000;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	PhysicsManager::Instance()->RegisterObject(this, PhysicsManager::CollisionLayers::Hostile);
}

Obstacle::~Obstacle() {
	delete mTexture;
	mTexture = nullptr;
}

bool Obstacle::IgnoreCollisions() {
	return mLives <= 0;
}

void Obstacle::Hit(PhysObject* other) {
	if (other->Name() == "Bullet") {
		mLives--;
		std::cout << mLives << "\n";
	}
}

void Obstacle::Update() {
	//IgnoreCollisions();//----------------/!
}

void Obstacle::Render() {
	mTexture->Render();
	PhysObject::Render();
}