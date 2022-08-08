// PacMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

int main()
{
    Game* GameInstance = new Game();
    GameInstance->Init();

    return 0;
}
