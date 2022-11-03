#include "Aliens.h"
#include "Window.h"
#include "Random.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Assets.h"
#include "Laser.h"
#include "Game.h"

MoveComponent* m_moveComponent;

Aliens::Aliens() : Actor()
{
	Vector2 randPos = Random::getVector(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
	setPosition(randPos);

	SpriteComponent* sc = new  SpriteComponent(this, Assets::getTexture("Aliens"));
	m_moveComponent = new MoveComponent(this);
	m_moveComponent->setForwardSpeed(-30);

	collision = new CircleCollisionComponent(this);
	collision->setRadius(20.0f);

	getGame().addAstroid(this);
}

Aliens::~Aliens()
{
	getGame().removeAstroid(this);
}

void Aliens::setSpeed(float forwardSpeedP)
{
	m_moveComponent->setForwardSpeed(forwardSpeedP);
}

void Aliens::shootLaser()
{
	Laser* laser = new Laser();
	laser->setTargetPlayer(true);
	laser->setPosition(getPosition());
	laser->setRotation(-3.14/2);
}
