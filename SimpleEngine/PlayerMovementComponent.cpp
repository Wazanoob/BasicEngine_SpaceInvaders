#include "PlayerMovementComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* ownerP, int updateOrderP) 
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f), horizontalSpeed(0.0f)
{

}

void PlayerMovementComponent::setHorizontalSpeed(float horizontalSpeedP)
{
	horizontalSpeed = horizontalSpeedP;
}

void PlayerMovementComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void PlayerMovementComponent::update(float dt)
{
	float radius = owner.getScale() * 20.0f;

	if (!Maths::nearZero(forwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed *  dt;

		// Screen blocking (for ship)
		if (newPosition.y < radius)
		{
			newPosition.y = radius;
		}
		else if (newPosition.y > WINDOW_HEIGHT - radius)
		{
			newPosition.y = WINDOW_HEIGHT - radius;
		}

		owner.setPosition(newPosition);
	}

	if (!Maths::nearZero(horizontalSpeed))
	{
		Vector2 newPosition = owner.getPosition() + Vector2(1, 0) * horizontalSpeed * dt;


		// Screen blocking (for ship)
		if (newPosition.x < radius)
		{
			newPosition.x = radius;
		}
		else if (newPosition.x > WINDOW_WIDTH - radius)
		{
			newPosition.x = WINDOW_WIDTH - radius;
		}

		owner.setPosition(newPosition);
	}
}
