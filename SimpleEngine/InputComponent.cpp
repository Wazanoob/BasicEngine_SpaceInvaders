#include "InputComponent.h"
#include "SDL_scancode.h"

InputComponent::InputComponent(Actor* ownerP):
	PlayerMovementComponent(ownerP),
	maxHorizontalSpeed(500.0f),
	maxForwardSpeed(300.0f),
	forwardKey(SDL_SCANCODE_W),
	backKey(SDL_SCANCODE_S),
	clockwiseKey(SDL_SCANCODE_D),
	counterClockwiseKey(SDL_SCANCODE_A)
{
}

void InputComponent::processInput(const Uint8* keyState)
{
	float horizontalSpeed = 0.0f;

	if (keyState[clockwiseKey])
	{
		horizontalSpeed += maxHorizontalSpeed;
	}
	if (keyState[counterClockwiseKey])
	{
		horizontalSpeed -= maxHorizontalSpeed;
	}
	setHorizontalSpeed(horizontalSpeed);


	//No forward speed needed
	//float forwardSpeed = 0.0f;

	//if (keyState[forwardKey])
	//{
	//	forwardSpeed += maxForwardSpeed;
	//}
	//if (keyState[backKey])
	//{
	//	forwardSpeed -= maxForwardSpeed;
	//}
	//setForwardSpeed(forwardSpeed);
}

void InputComponent::setMaxHorizontalSpeed(float maxHorizontalSpeedP)
{
	maxHorizontalSpeed = maxHorizontalSpeedP;
}

void InputComponent::setMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::setForwardKey(int key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(int key)
{
	backKey = key;
}

void InputComponent::setClockwiseKey(int key)
{
	clockwiseKey = key;
}

void InputComponent::setCounterClockwiseKey(int key)
{
	counterClockwiseKey = key;
}
