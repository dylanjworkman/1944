
#include "pch.h"
#include "SDLGame.h"
//main CPP file that initialises and runs the SDL Game in a new window
int main(int argc, char* args[])
{
	SDLGame* mainGame = new SDLGame();

	mainGame->initialise();
	mainGame->runGameLoop();

	return 0;
}

