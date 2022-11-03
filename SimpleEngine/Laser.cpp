#include "Laser.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "ProjectileMoveComponent.h"
#include "Game.h"
#include "Aliens.h"

Laser::Laser() :
	Actor(),
	deathTimer(1.0f),
	collision(nullptr)
{
	new SpriteComponent(this, Assets::getTexture("Laser"));
	ProjectileMoveComponent* mc = new ProjectileMoveComponent(this);
	mc->setForwardSpeed(600.0f);
	collision = new CircleCollisionComponent(this);
	collision->setRadius(11.0f);
}

void Laser::updateActor(float dt)
{
	deathTimer -= dt;
	if (deathTimer <= 0.0f)
	{
		setState(Actor::ActorState::Dead);
	}
	else if(!fromEnemy)
	{
		auto astroids = getGame().getAstroids();
		for (auto astroid : astroids)
		{
			if (Intersect(*collision, astroid->getCollision()))
			{
				setState(ActorState::Dead);
				astroid->setState(ActorState::Dead);
				break;
			}
		}
	}
	else if(fromEnemy)
	{
		auto ship = getGame().getPlayer();
		if (Intersect(*collision, ship[0]->getCollision()))
		{
			setState(ActorState::Dead);
			ship[0]->setState(ActorState::Paused);

			getGame().close();
		}
	}
}

void Laser::setTargetPlayer(bool b)
{
	fromEnemy = b;
}
