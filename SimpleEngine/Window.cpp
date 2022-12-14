#include "Window.h"
#include "Log.h"

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult !=0 )
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL");
		return false;
	}

	SDLWindow = SDL_CreateWindow("My little Spaceship", 100, 100, m_width, m_height, 0);
	if (!SDLWindow)
	{
		Log::error(LogCategory::System, "Failed to create window");
		return false;
	}

	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}



