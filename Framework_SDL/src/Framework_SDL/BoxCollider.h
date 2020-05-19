#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "Collider.h"

class BoxCollider : public Collider {

private:
	static const int MAX_VERTS = 4;

	GameObject* mVerts[MAX_VERTS];

public:
	BoxCollider(Vector2 size);
	~BoxCollider();

	Vector2 GetFurthestPoint() override;

	Vector2 GetVertexPos(int index);
private:
	void AddVert(int index, Vector2 pos);
};
#endif // !BOXCOLLIDER_H
