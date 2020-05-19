#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H
#include "Collider.h"
#include <vector>

class PhysObject : public GameObject {
protected:

	unsigned long mId;

	std::vector<Collider*>mColliders;

	Collider* mBroadPhaseCollider;
public:
	PhysObject();
	virtual ~PhysObject();

	unsigned long GetId();

	bool CheckCollision(PhysObject* other);

	virtual void Hit(PhysObject* other);

	virtual void Render();
protected:

	virtual bool IgnoreCollisions();

	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};
#endif // !PHYSOBJECT_H
