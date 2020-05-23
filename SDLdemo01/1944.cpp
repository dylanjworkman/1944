
#include "pch.h"
#include "SDLGame.h"

int main(int argc, char* args[])
{
	SDLGame* mainGame = new SDLGame();

	mainGame->initialise();
	mainGame->runGameLoop();

	return 0;
}

