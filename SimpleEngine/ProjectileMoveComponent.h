#pragma once
#include "Component.h"
class ProjectileMoveComponent :
    public Component
{
public:
    ProjectileMoveComponent(Actor* ownerP, int updateOrder = 10); // By default, update before other components
    ProjectileMoveComponent() = delete;
    ProjectileMoveComponent(const ProjectileMoveComponent&) = delete;
    ProjectileMoveComponent& operator =(const ProjectileMoveComponent&) = delete;

    float getForwardSpeed() const { return forwardSpeed; }

    void setForwardSpeed(float forwardSpeedP);

    void update(float dt) override;

private:
    float forwardSpeed;
};

