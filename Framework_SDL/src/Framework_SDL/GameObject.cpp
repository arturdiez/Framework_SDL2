#include "GameObject.h"

//Constructor & Destructor
GameObject::GameObject(Vector2 pos) {
	mPos = pos;
	mRotation = 0.0f;
	mScale = VEC2_ONE;
	mActive = true;
	mParent = nullptr;
}
GameObject::~GameObject() {
	mParent = nullptr;
}

//Getter & Setter Name of GO
void GameObject::Name(std::string name) {
	mName = name;
}

std::string GameObject::Name() {
	return mName;
}

//Getter & Setter Position of GO
void GameObject::Pos(Vector2 pos) {
	mPos.x = pos.x;
	mPos.y = pos.y;
}
Vector2 GameObject::Pos(SPACE space) {
	if (space == local || mParent == nullptr) { return mPos; }

	GameObject* parent = mParent;
	Vector2 finalPos = mPos, parentScale = VEC2_ZERO;

	do
	{
		//Transform(Rotation(Scale Point))
		Vector2 parentScale = mParent->Scale(local);
		finalPos = RotateVector(Vector2(finalPos.x * parentScale.x, finalPos.y * parentScale.y), parent->Rotation(local));
		finalPos += parent->Pos(local);

		parent = parent->Parent();

	} while (parent);
		

	return finalPos;
}

//Getter & Setter Rotation of GO
void GameObject::Rotation(float rotation) {
	mRotation = rotation;
	if (mRotation > 360.0f) {
		int mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if (mRotation < 0.0f) {
		int mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}
float GameObject::Rotation(SPACE space) {
	if (space == local || mParent == nullptr) { return mRotation; }
	return mParent->Rotation(world) + mRotation;
}

//Getter & Setter Scale of GO
void GameObject::Scale(Vector2 scale) {
	mScale = scale;
}
Vector2 GameObject::Scale(SPACE space) {
	if (space == local || mParent == nullptr) { return mScale; }
	Vector2 scale = mParent->Scale(world);

	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

//Getter and Setter Active GO
void GameObject::Active(bool active) {
	mActive = active;
}
bool GameObject::Active() {
	return mActive;
}

//Getter & Setter Parent
void GameObject::Parent(GameObject* parent) {
	if (parent == nullptr) {
		mPos = Pos(world);
		mScale = Scale(world);
		mRotation = Rotation(world);
	}
	else {
		if (mParent != nullptr) {
			Parent(nullptr);
		}
		Vector2 parentScale = parent->Scale(world);
		mPos = RotateVector(Vector2(Pos(world) - parent->Pos(world)), -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		mRotation = mRotation - parent->Rotation(world);

		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);

	}
	mParent = parent;
}
GameObject* GameObject::Parent() {
	return mParent;
}

//Translate & Rotate of GO
void GameObject::Translate(Vector2 vector, SPACE space) {
	if (space == world) {
		mPos += vector;
	}
	else {
		mPos += RotateVector(vector, Rotation());
	}
	
}
void GameObject::Rotate(float amount) {
	mRotation += amount;
}


//Update & Render of GO
void GameObject::Update() {}
void GameObject::Render() {}