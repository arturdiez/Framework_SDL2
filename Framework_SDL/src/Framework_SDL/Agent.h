#pragma once
#include <minmax.h>
#include "Math.h"
#include "SteeringBehavior.h"
#include "Path.h"
#include "Sprite.h"


class Agent : public GameObject
{
	friend class SteeringBehavior;

private:
	SteeringBehavior *steering_behavior;
	Timer* mTimer;
	Texture* mTexture;

	Vector2 position;
	Vector2 velocity;
	Vector2 target;

	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

public:
	Agent();
	~Agent();
	void addPathPoint(Vector2 point);
	int getCurrentTargetIndex();
	void setCurrentTargetIndex(int idx);
	SteeringBehavior *Behavior();
	Vector2 getPosition();
	Vector2 getTarget();
	Vector2 getVelocity();
	float getMaxVelocity();
	void setPosition(Vector2 position);
	void setTarget(Vector2 target);
	void setVelocity(Vector2 velocity);
	void setMass(float mass);
	void Update(Vector2 steering_force, float dtime);
	void Render();
	//void draw();
	//bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	Vector2 getNextPathPoint();
};
