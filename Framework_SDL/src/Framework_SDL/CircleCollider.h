#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H
#include "Collider.h"

class CircleCollider : public Collider {

private:
	float mRadius;
public:
	CircleCollider(float radius, bool broadPhase = false);
	~CircleCollider();

	Vector2 GetFurthestPoint() override;
};

#endif // !CIRCLECOLLIDER_H

