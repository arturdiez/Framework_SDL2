#include "PhysObject.h"
#include "PhysicsManager.h"
#include "PhysicsHelper.h"

PhysObject::PhysObject() {

	mBroadPhaseCollider = nullptr;
	mId = 0;
}

PhysObject::~PhysObject() {
	for (int i = 0; i < mColliders.size(); i++) {
		delete mColliders[i];
		mColliders[i] = nullptr;
	}

	mColliders.clear();
	if (mBroadPhaseCollider) {
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}

	if (mId != 0) {
		PhysicsManager::Instance()->UnregisterObject(mId);
	}
}

unsigned long PhysObject::GetId() {
	return mId;
}

bool PhysObject::CheckCollision(PhysObject* other) {
	
	if (IgnoreCollisions() || other->IgnoreCollisions()) {
		return false;
	}
		
	return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
}

void PhysObject::Hit(PhysObject* hit) {
	
}

bool PhysObject::IgnoreCollisions() {

	return false;
}

void PhysObject::AddCollider(Collider* collider, Vector2 localPos) {
	collider->Parent(this);
	collider->Pos(localPos);
	mColliders.push_back(collider);

	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle) {
		float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
		float dist = 0.0f;
		for (int i = 1; i < mColliders.size(); i++) {
			dist = mColliders[i]->GetFurthestPoint().Magnitude();
			if (dist > furthestDistance) {
				furthestDistance = dist;
			}
		}

		delete mBroadPhaseCollider;
		mBroadPhaseCollider = new CircleCollider(furthestDistance,true);
		mBroadPhaseCollider->Parent(this);
		mBroadPhaseCollider->Pos(VEC2_ZERO);
	}
}

void PhysObject::Render() {
	for (int i = 0; i < mColliders.size(); i++) {
		mColliders[i]->Render();
	}
	if(mBroadPhaseCollider){
		mBroadPhaseCollider->Render();
	}
}

