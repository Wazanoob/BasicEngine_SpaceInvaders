#include "Ship.h"
#include "Maths.h"
#include "Assets.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "Laser.h"
#include "Game.h"

Ship::Ship() : Actor(), laserCooldown(0.0f)
{
	//Animated Sprite
	vector<Texture*> animTextures
	{
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04")
	};

	SpriteComponent* animatedSprite = new AnimSpriteComponent(this, animTextures);
	//SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));

	InputComponent* ic = new InputComponent(this);

	ic->setMaxHorizontalSpeed(300.0f);
	ic->setMaxForwardSpeed(500.0f);

	collision = new CircleCollisionComponent(this);
	collision->setRadius(10.0f);

	getGame().addShip(this);
}

Ship::~Ship()
{
	getGame().removeShip(this);
}

void Ship::actorInput(const Uint8* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f)
	{
		Laser* laser = new Laser();
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());
		laserCooldown = 0.2f;
	}
}

void Ship::updateActor(float dt)
{
	laserCooldown -= dt;
}
