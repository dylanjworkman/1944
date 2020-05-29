#pragma once

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "SpawnPosition.h"
#include "KeyFlags.h"
#include "ProjectileType.h"
#include "BulletInstance.h"

class SDLGame {

private:

	bool gameRunning;

	//SDL game window and renderer
	SDL_Window*		gameWindow = nullptr;
	SDL_Renderer*	gameRenderer = nullptr;

	//main player sprites
	Sprite*			sprite = nullptr;
	Player*			mainPlayer = nullptr;

	//enemy and pickups
	Enemy* enemySprite = nullptr;
	Pickup* pickupSprite = nullptr;

	//keyboard input/keyflags
	KeyFlags		keyState = 0;

	//timing (delta and time index)
	uint32_t		currentTimeIndex, prevTimeIndex, timeDelta;
	float			timeDeltaInSeconds;

	//main player/user gamepad controls (xbox 360/one input aka XINPUT)
	SDL_GameController* controllers[4] = { nullptr, nullptr, nullptr, nullptr };
	
	//joystick current state and events
	Sint16			lx = 0, ly = 0; // Left controller joystick movement for mainPlayer
	Sint16			rx = 0; // Right controller (x axis rotation) for mainPlayer

	//Bullets/projectiles
	static const int MAX_BULLETS = 1000;

	Sprite* bulletSprite = nullptr;
	ProjectileType* bulletType = nullptr;

	BulletInstance* bullets[MAX_BULLETS];


	//gameloop
	void handleEvents();
	void update();
	void draw();

public:

	SDLGame();
	~SDLGame();

	void initialise();
	void runGameLoop();

};

