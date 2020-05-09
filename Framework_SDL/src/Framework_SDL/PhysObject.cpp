#include "PhysObject.h"
#include "CircleCollider.h"

PhysObject::PhysObject() {
	mBroadPhaseCollider = nullptr;
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

