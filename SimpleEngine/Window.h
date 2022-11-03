#pragma once
#include "SDL.h"

constexpr int WINDOW_WIDTH = 1024;
constexpr int WINDOW_HEIGHT = 768;

class Window
{
public:
	Window() = default;
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;

	bool initialize();
	void close();

	SDL_Window* getSDLWindow() const { return SDLWindow; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

private:
	SDL_Window* SDLWindow {nullptr};
	int m_width { WINDOW_WIDTH };
	int m_height { WINDOW_HEIGHT };

};

