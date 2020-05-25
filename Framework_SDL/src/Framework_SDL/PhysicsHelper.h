#ifndef PHYSICSHELPER_H
#define PHYSICSHELPER_H

#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"

//Retorna true si el punto se encuentra dentro del poligono
inline bool PointInPolygon(Vector2* verts, int vertCount, const Vector2& point) {

	bool retVal = false;

	for (int i = 0, j = vertCount - 1 < vertCount; j - i++;) {
		if ((verts[i].y >= point.y) != (verts[j].y >= point.y)) { //descartar segmentos por encima o debajo del punto
			Vector2 vec1 = (verts[i] - verts[j]).Normalized(); //normalizar segmento entre vertices
			Vector2 proj = verts[j] +  vec1 * Dot(point - verts[j], vec1); //proyectar el punto en el segmento
			if (proj.x > point.x) {
				retVal = !retVal;
			}
		}
	}

	return retVal;
}
//Retorna la distancia del punto mas cercano a otro punto contenido en un segmento
inline float PointToLineDistance(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point) {
	//pendiente de la recta
	Vector2 slope = lineEnd - lineStart;

	//Proyeccion a partir del punto (radio) y el inicio del segmento (vertice)
	//el clamp actua a modo de seleccionar el punto dentro del segmento (lineend - linestart) que conforman dos vertices
	float param = Clamp(Dot(point - lineStart , slope) / slope.MagnitudeSqr(), 0.0f, 1.0f);


	Vector2 nearestPoint = lineStart + slope * param;

	return (point - nearestPoint).Magnitude();
}

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2) {

	return(c1->Pos() - c2->Pos()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxCircleCollision(BoxCollider* box, CircleCollider* circle) {

	Vector2 quad[4];
	quad[0] = box->GetVertexPos(0);
	quad[1] = box->GetVertexPos(1);
	quad[2] = box->GetVertexPos(2);
	quad[3] = box->GetVertexPos(3);

	float radius = circle->GetRadius();
	Vector2 circlePos = circle->Pos();

	//check if any vertex is inside circle
	for (int i = 0; i < 4; i++) { 
		if ((quad[i] - circlePos).Magnitude() < radius) {
			return true;
		}
	}
	//Check if segment is inside circle
	if (PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(1), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(2), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(2), box->GetVertexPos(3), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(3), box->GetVertexPos(1), circlePos) < radius)
	{
		return true;
	}

	//Check if circle is inside polygon
	if (PointInPolygon(quad, 4, circlePos)) {
		
		return true;
	}

	return false;
}
//SAT
inline bool BoxBoxCollision(BoxCollider* b1, BoxCollider* b2) {
	Vector2 projAxis[4];

	projAxis[0] = (b1->GetVertexPos(0) - b1->GetVertexPos(1)).Normalized();
	projAxis[1] = (b1->GetVertexPos(0) - b1->GetVertexPos(2)).Normalized();
	projAxis[2] = (b2->GetVertexPos(0) - b2->GetVertexPos(1)).Normalized();
	projAxis[3] = (b2->GetVertexPos(0) - b2->GetVertexPos(2)).Normalized();

	float b1Min = 0.0f, b1Max = 0.0f;
	float b2Min = 0.0f, b2Max = 0.0f;
	float proj1 = 0.0f, proj2 = 0.0f;

	for (int i = 0; i < 4; i++) { //projection of vertex
		for (int j = 0; j < 4; j++) {
			proj1 = Dot(b1->GetVertexPos(j), projAxis[i]);
			proj2 = Dot(b2->GetVertexPos(j), projAxis[i]);

			if (j == 0) {
				b1Min = b1Max - proj1;
				b2Min = b2Max - proj2;
			}
			else {
				//first box
				if (proj1 < b1Min) {
					b1Min = proj1;
				}
				if (proj1 > b1Max) {
					b1Max = proj1;
				}
				//second box
				if (proj2 < b2Min) {
					b2Min = proj2;
				}
				if (proj2 > b2Max) {
					b2Max = proj2;
				}
			}
		}
		float halfDist1 = (b1Max - b1Min) * 0.5f;
		float midPoint1 = b1Min + halfDist1;

		float halfDist2 = (b2Max - b2Min) * 0.5f;
		float midPoint2 = b2Min + halfDist2;

		//overlap of projections
		if (abs(midPoint1 - midPoint2) > (halfDist1 + halfDist2)) {
			return false;
		}
	}
	return true;
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2) {

	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle) {
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Circle) {
		return BoxCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c2->GetType() == Collider::ColliderType::Box && c1->GetType() == Collider::ColliderType::Circle) {
		return BoxCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
	}
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Box) {
		return BoxBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
	}
	else {
		return false;
	}

}

#endif // !PHISICSHELPER_H

