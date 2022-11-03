#include "Game.h"
#include "Assets.h"
#include "Aliens.h"
#include "Random.h"
#include "Ship.h"
#include "Timer.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "BackgroundSpriteComponent.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit;
}

void Game::load()
{
	//Load Textures
	Assets::loadTexture(renderer, "Res\\Ship01.png", "Ship01");
	Assets::loadTexture(renderer, "Res\\Ship02.png", "Ship02");
	Assets::loadTexture(renderer, "Res\\Ship03.png", "Ship03");
	Assets::loadTexture(renderer, "Res\\Ship04.png", "Ship04");
	Assets::loadTexture(renderer, "Res\\FarBack01.png", "Farback01");
	Assets::loadTexture(renderer, "Res\\FarBack02.png", "Farback02");
	Assets::loadTexture(renderer, "Res\\Stars.png", "Stars");
	Assets::loadTexture(renderer, "Res\\Aliens.png", "Aliens");
	Assets::loadTexture(renderer, "Res\\Ship.png", "Ship");
	Assets::loadTexture(renderer, "Res\\Laser.png", "Laser");

	////Single Sprite (No animations)
	//Actor* actor = new Actor();
	//SpriteComponent* sprite = new SpriteComponent(actor, Assets::getTexture("Ship01"));
	//actor->setPosition(Vector2{ 100 , 100 });

	////Animated Sprite
	//vector<Texture*> animTextures
	//{
	//	&Assets::getTexture("Ship01"),
	//	&Assets::getTexture("Ship02"),
	//	&Assets::getTexture("Ship03"),
	//	&Assets::getTexture("Ship04")
	//};

	//Actor* ship = new Actor();
	//SpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTextures);
	//ship->setPosition(Vector2{ 100, 300 });

	float piOver2 = 3.1415926535f / 2;

	//Controller Ship
	Ship* ship = new Ship();
	ship->setPosition(Vector2{ WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100 });
	ship->setRotation(piOver2);

	//Background
	//Create the "far Back" background
	vector<Texture*> bgTexsFar
	{
		&Assets::getTexture("Farback01"),
		&Assets::getTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->setScrollSpeed(0.0f);

	// Create the closer background
	Actor* bgClose = new Actor();
	std::vector<Texture*> bgTexsClose
	{
		&Assets::getTexture("Stars"),
		&Assets::getTexture("Stars")
	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTexsClose, 50);
	bgSpritesClose->setScrollSpeed(200.0f);

	spawnEnemy();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;

	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;

		processInput();
		update(dt);
		updateAstroids();
		render();

		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// resources
	Assets::clear();
}

void Game::close()
{
	window.close();
	renderer.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	//Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		//Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}

}

vector<Aliens*>& Game::getAstroids()
{
	return astroids;
}

vector<Ship*>& Game::getPlayer()
{
	return ship;
}

void Game::addAstroid(Aliens* astroid)
{
	astroids.emplace_back(astroid);
}

void Game::addShip(Ship* shipP)
{
	ship.emplace_back(shipP);
}

void Game::removeAstroid(Aliens* astroid)
{
	auto iter = std::find(begin(astroids), end(astroids), astroid);
	if (iter != astroids.end())
		astroids.erase(iter);
}

void Game::removeShip(Ship* shipP)
{
	auto iter = std::find(begin(ship), end(ship), shipP);
	if (iter != ship.end())
		ship.erase(iter);
}

void Game::processInput()
{
	//SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	//Keyboard State
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	//Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;

}

void Game::update(float dt )
{
	//Update actors
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	//Aliens Shoot
	timer += dt;

	if (timer > 0.4f)
	{
		int randomFire = Random::getIntRange(0, astroids.size() - 1);
		astroids[randomFire]->shootLaser();

		timer = 0;
	}

	//Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::updateAstroids()
{
	if (moveLeft && !onlyOnce)
	{
		moveRight = false;

		for (auto astroid : astroids)
		{
			Vector2 nextPosition = astroid->getPosition() + Vector2{ 0, 35 };

			astroid->setPosition(nextPosition);
		}

		onlyOnce = true;
	}

	if (moveRight && !onlyOnce)
	{
		moveLeft = false;

		for (auto astroid : astroids)
		{
			Vector2 nextPosition = astroid->getPosition() + Vector2{ 0, 35 };

			astroid->setPosition(nextPosition);
		}

		onlyOnce = true;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::spawnEnemy()
{
	//Spawn a wall of aliens
	const int widthCount = 13;
	const int heightCount = 5;
	float posX = 100;
	float posY = 50;

	//First Wave
	for (int h = 0; h < heightCount; ++h)
	{
		for (int i = 0; i < widthCount; ++i)
		{
			Aliens* astroidP = new Aliens();
			astroidP->setPosition({ posX, posY });

			posX += 65;
		}
		posX = 100;
		posY += 70;
	}
}
