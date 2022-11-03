#pragma once
#include "Actor.h"
#include "CircleCollisionComponent.h"

class Laser :
    public Actor
{
public:
    Laser();

    void updateActor(float dt) override;
    void setTargetPlayer(bool b);

private:
    CircleCollisionComponent* collision;
    bool fromEnemy = false;
    float deathTimer;
};

