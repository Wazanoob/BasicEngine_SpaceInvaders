#pragma once
#include  "Actor.h"
#include  "CircleCollisionComponent.h"

class Aliens : public Actor
{
public:
	Aliens();
	~Aliens();

	void setSpeed(float forwardSpeedP);
	void shootLaser();

	CircleCollisionComponent& getCollision() { return *collision; }

private:
	CircleCollisionComponent* collision;
};

