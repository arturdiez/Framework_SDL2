#include "Obstacle.h"

Obstacle::Obstacle() {
	mTexture = new Texture("Tile.png", 0, 0, 32, 32);
	mTexture->Parent(this);
	mTexture->Scale(Vector2(2, 2));

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
}

Obstacle::~Obstacle() {
	delete mTexture;
	mTexture = nullptr;
}
void Obstacle::Update() {


}

void Obstacle::Render() {
	mTexture->Render();
	PhysObject::Render();
}