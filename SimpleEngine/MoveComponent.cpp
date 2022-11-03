#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Game.h"
#include "Aliens.h"
#include "Window.h"

//Move the enemy

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP) 
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f)
{
	
}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::update(float dt)
{
	if (owner.getGame().moveRight)
	{
		forwardSpeed = 30;
	}

	if (owner.getGame().moveLeft)
	{
		forwardSpeed = -30;
	}

	Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;

	if (newPosition.x < 0 + owner.getScale() * 20)
	{
		owner.getGame().onlyOnce = false;
		owner.getGame().moveRight = true;
	}else if (newPosition.x > WINDOW_WIDTH - owner.getScale() * 20)
	{
		owner.getGame().onlyOnce = false;
		owner.getGame().moveLeft = true;
	}else
		owner.setPosition(newPosition);

}
