#pragma once
#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Actor.h"
#include "Aliens.h"
#include "Ship.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator = (const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator = (Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false) {}

public:
	bool initialize();
	bool moveLeft { false };
	bool moveRight { false };
	bool onlyOnce { false };
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	//GameSpecific
	vector<Aliens*>& getAstroids();
	vector<Ship*>& getPlayer();
	void addAstroid(Aliens* astroid);
	void addShip(Ship* shipP);
	void removeAstroid(Aliens* astroid);
	void removeShip(Ship* shipP);

	Renderer& getRenderer() { return renderer; }

private:
	void processInput();
	void update(float dt);
	void updateAstroids();
	void render();

	void spawnEnemy();

	//GameSpecific
	vector<Aliens*> astroids;
	vector<Ship*> ship;

	Window window{};
	Renderer renderer{};
	bool isRunning {true};
	float  timer = 0;

	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	bool isUpdatingActors;
};

