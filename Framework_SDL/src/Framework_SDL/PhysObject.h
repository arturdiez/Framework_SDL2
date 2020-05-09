#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H
#include "Collider.h"
#include <vector>

class PhysObject : public GameObject {
protected:
	std::vector<Collider*>mColliders;

	Collider* mBroadPhaseCollider;
public:
	PhysObject();
	virtual ~PhysObject();
	virtual void Render();
protected:
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};
#endif // !PHYSOBJECT_H
