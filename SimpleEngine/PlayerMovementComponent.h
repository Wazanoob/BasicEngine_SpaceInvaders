#pragma once
#include "Component.h"

class PlayerMovementComponent :
    public Component
{
public:
    PlayerMovementComponent(Actor* ownerP, int updateOrderP = 10); // By default, update before other components
    PlayerMovementComponent() = delete;
    PlayerMovementComponent(const PlayerMovementComponent&) = delete;
    PlayerMovementComponent& operator =(const PlayerMovementComponent&) = delete;

    void setForwardSpeed(float forwardSpeedP);
    void setHorizontalSpeed(float horizontalSpeedP);

    void update(float dt) override;

private:
    float forwardSpeed;
    float horizontalSpeed;
};

