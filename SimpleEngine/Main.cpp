#include <iostream>
#include "SDL.h"
#include "Log.h"
#include "Game.h"

int main(int argc, char** argv)
{
    Game& instance = Game::instance();
    bool isGameInit = instance.initialize();

    if (isGameInit)
    {
        instance.load();
        instance.loop();
        instance.unload();
    }

    instance.close();
    return 0;
}