#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "Actor.h"

class Window;
class Rectangle;
class SpriteComponent;
class Texture;

class Renderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	
	Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void draw();
	void drawRect(const Rectangle& rect);
	void addSprite(SpriteComponent* sprite);
	void removeSprite(SpriteComponent* sprite);
	void drawSprites();
	void drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	void endDraw();
	void close();

	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

private:
	SDL_Renderer* SDLRenderer = nullptr;
	std::vector<SpriteComponent*>  sprites;
};

