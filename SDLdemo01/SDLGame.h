#pragma once

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "KeyFlags.h"
#include "ProjectileType.h"
#include "BulletInstance.h"

class SDLGame {

private:

	bool gameRunning;

	// The game object will own the window and renderer objects
	SDL_Window*		gameWindow = nullptr;
	SDL_Renderer*	gameRenderer = nullptr;

	// Sprite for in-game characters
	Sprite*			sprite = nullptr;
	Player*			mainPlayer = nullptr;

	// Recipe 2 - Keyboard input
	KeyFlags		keyState = 0;

	// Recipe 3 - Timing attributes
	uint32_t		currentTimeIndex, prevTimeIndex, timeDelta;
	float			timeDeltaInSeconds;

	// Recipe 4 - Player control using a controller
	// For now, mainPlayer will use only controllers[0] when connected ie. First controller connected to the system
	SDL_GameController* controllers[4] = { nullptr, nullptr, nullptr, nullptr };
	
	// Capture relevant joystick state in Game Object attributes...
	Sint16			lx = 0, ly = 0; // Left controller joystick movement for mainPlayer
	Sint16			rx = 0; // Right controller (x axis rotation) for mainPlayer
	
	// Recipe 5 & 9 - Something to collide with and shoot
	Enemy*			enemySprite = nullptr;

	// Recipe 9 - Bullets
	static const int MAX_BULLETS = 1000;

	Sprite* bulletSprite = nullptr;
	ProjectileType* bulletType = nullptr;

	BulletInstance* bullets[MAX_BULLETS];


	// Private API
	void handleEvents();
	void update();
	void draw();

public:

	SDLGame();
	~SDLGame();

	void initialise();
	void runGameLoop();

};

