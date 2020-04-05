#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Math.h"

class GameObject {
	//Variables
public:
	enum SPACE {local = 0, world = 1};
private:
	Vector2 mPos;
	float mRotation;
	Vector2 mScale;

	bool mActive;
	GameObject* mParent;

	//Functions
public:
	//Constructor & Deconstructor
	GameObject(Vector2 pos = VEC2_ZERO);
	~GameObject();

	//Getter & Setter Position
	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = world);

	//Getter & Setter Rotation
	void Rotation(float rotation);
	float Rotation(SPACE space = world);

	//Getter & Setter Scale
	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = world);

	//Getter & Setter Active
	void Active(bool active);
	bool Active();

	//Getter & Setter Parent
	void Parent(GameObject* parent);
	GameObject* Parent();

	//Move, Rotate GO
	void Translate(Vector2 vector, SPACE space = local);
	void Rotate(float amount);

	//Inherited in children
	virtual void Update();
	virtual void Render();
};

#endif 
