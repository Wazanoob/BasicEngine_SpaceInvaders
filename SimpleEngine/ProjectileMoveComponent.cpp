#include "ProjectileMoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

//Move the projectiles

ProjectileMoveComponent::ProjectileMoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f)
{

}

void ProjectileMoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void ProjectileMoveComponent::update(float dt)
{
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;

		owner.setPosition(newPosition);
	}
}
