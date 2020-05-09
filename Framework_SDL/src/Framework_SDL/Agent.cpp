#include "Agent.h"

using namespace std;

Agent::Agent() {
	mTimer = Timer::Instance();

	mTexture = new Texture("Agent.png", 0, 0, 64, 64);
	mTexture->Parent(this);
	mTexture->Scale(Vector2(0.5f, 0.5f));
	mTexture->Pos(Vector2(150, 150));

	velocity = Vector2(0, 0);
	mass = 0.1f;
	max_force = 150;
	max_velocity = 200;
	orientation = 0;
	currentTargetIndex = -1;
	steering_behavior = new SteeringBehavior;
}

Agent::~Agent()
{
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

void Agent::addPathPoint(Vector2 point)
{
	if (path.points.size() > 0)
		if (path.points[path.points.size() - 1] == point)
			return;

	path.points.push_back(point);
}

int Agent::getCurrentTargetIndex()
{
	return currentTargetIndex;
}

void Agent::setCurrentTargetIndex(int idx)
{
	currentTargetIndex = idx;
}

SteeringBehavior * Agent::Behavior()
{
	return steering_behavior;
}

Vector2 Agent::getPosition()
{
	return position;
}

Vector2 Agent::getTarget()
{
	return target;
}

Vector2 Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

void Agent::setPosition(Vector2 _position)
{
	position = _position;
}

void Agent::setTarget(Vector2 _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2 _velocity)
{
	velocity = _velocity;
}

void Agent::setMass(float _mass)
{
	mass = _mass;
}



void Agent::Update(Vector2 steering_force, float dtime)
{
	

	Vector2 acceleration = steering_force / mass;
	velocity = velocity + acceleration * dtime;
	if (velocity.Magnitude() > max_velocity)
		velocity = velocity.Normalized() * max_velocity;
	

	position = position + velocity * dtime;
	mTexture->Pos(position);
	// Update orientation
	if (velocity.Magnitude()>0)
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD_TO_DEG);
}


void Agent::Render() {
	mTexture->Render();
}

Vector2 Agent::getNextPathPoint()
{
	return path.points.front();
}
