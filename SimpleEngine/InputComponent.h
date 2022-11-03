#pragma once
#include "PlayerMovementComponent.h"
#include "SDL_stdinc.h"


class InputComponent :
    public PlayerMovementComponent
{
public:
    InputComponent(Actor* ownerP);
    InputComponent() = delete;
    InputComponent(const InputComponent&) = delete;
    InputComponent& operator =(const InputComponent&) = delete;

    void processInput(const Uint8* keyState);

    void setMaxHorizontalSpeed(float maxHorizontalSpeedP);
    void setMaxForwardSpeed(float maxForwardSpeedP);
    void setForwardKey(int key);
    void setBackKey(int key);
    void setClockwiseKey(int key);
    void setCounterClockwiseKey(int key);

private:
    float maxHorizontalSpeed;
    float maxForwardSpeed;

    int forwardKey;
    int backKey;
    int clockwiseKey;
    int counterClockwiseKey;
};

