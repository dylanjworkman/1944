#include "pch.h"
#include "SDLGame.h"

//Contents:
//SDLGame.cpp
	//Initialisation
		//	gameWindow()
		//	gameRenderer()
	//GameLoop
		//	handleEvents()
		//	update()
		//	draw()

//SDL = Simple Directmedia Layer
SDLGame::SDLGame() {
	//Construct (allocates memory)
	gameWindow = nullptr;
	gameRenderer = nullptr;

	sprite = nullptr;
	mainPlayer = nullptr;
	enemySprite = nullptr;
	pickupSprite = nullptr;

}


SDLGame::~SDLGame() {
	//Deconstruct (wipes allocated memory)
	delete gameWindow;
	delete gameRenderer;

	delete sprite;
	delete mainPlayer;
	delete enemySprite;
	delete bulletSprite;
	delete pickupSprite;
}

//START OF INITIALISATION
void SDLGame::initialise() {

	const int SDL_OKAY = 0;

	int sdlStatus = SDL_Init(SDL_INIT_EVERYTHING);//initialise everything for SDL

	if (sdlStatus != SDL_OKAY)
		throw "SDL init error";

	gameWindow = SDL_CreateWindow(
		"1944",//Window name
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,//horizontal resolution (x)
		600,//vertical resolution (y)
		SDL_WINDOW_SHOWN);//shows window on-screen

	// Enumerate render drivers
	int n = SDL_GetNumRenderDrivers();

	printf("Number of renderers = %d\n", n);

	for (int i = 0; i < n; ++i) {

		SDL_RendererInfo renderInfo;

		if (SDL_GetRenderDriverInfo(i, &renderInfo) == 0) { // 0 = success

			printf("Renderer %d : %s\n", i, renderInfo.name);
		}
	}

	// renders gameWindow 
	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);

	//player sprite initialisation
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "Assets\\Images\\playerSprite.png");
	//v
	mainPlayer = new Player();
	mainPlayer->initialise(sprite, 375, 530, 100.0f);

	//enemy sprite initialisation
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "Assets\\Images\\enemySprite.png");
	//v
	enemySprite = new Enemy();
	enemySprite->initialise(sprite, 375, 10);
	//ATTEMPTED in enemy classes and headers to create an array that would allow multiple enemies to be rendered, updated, and drawn into the SDL game window
	// however after hours of testing could not find an efficient solution

	//pickup sprite initialisation
	sprite = new Sprite();
	sprite->initialise(gameRenderer, "Assets\\Images\\pickup.png");
	//v
	pickupSprite = new Pickup();
	pickupSprite->initialise(sprite, 150, 500);

	//bullet sprite initialisation
	bulletSprite = new Sprite();
	bulletSprite->initialise(gameRenderer, "Assets\\Images\\bullet.png");
	//v
	bulletType = new ProjectileType();
	bulletType->initialise(bulletSprite, 5, 600, 32, 32);

	for (int i = 0; i < MAX_BULLETS; i++) {
		
		bullets[i] = nullptr;
	}

	//additional initialisation code goes HERE!

}//END OF INITIALISATION

//START OF GAMELOOP
void SDLGame::runGameLoop() {

	gameRunning = true;

	while (gameRunning) {
		
		//Calculate time elapsed
		currentTimeIndex = SDL_GetTicks();
		timeDelta = currentTimeIndex - prevTimeIndex;
		timeDeltaInSeconds = float(timeDelta) / 1000.0f;

		// Store current time index into prevTimeIndex for next frame
		prevTimeIndex = currentTimeIndex;

		//key sections of game loop
		handleEvents();
		update();
		draw();
	}
}

void SDLGame::handleEvents() {

	SDL_Event event;
	Sint32 deviceID;
	Sint32 instanceID;

	// Check for next event
	while (SDL_PollEvent(&event)) {
		
		switch (event.type) {

		// Check if window closed
		case SDL_QUIT:
			gameRunning = false;
			break;

		// Key pressed event
		case SDL_KEYDOWN:

			// Toggle key states based on key pressed
			switch (event.key.keysym.sym) {

			case SDLK_UP:
				keyState |= Keys::Up;
				break;

			case SDLK_DOWN:
				keyState |= Keys::Down;
				break;

			case SDLK_LEFT:
				keyState |= Keys::Left;
				break;

			case SDLK_RIGHT:
				keyState |= Keys::Right;
				break;

			case SDLK_SPACE:
				keyState |= Keys::Fire;
				break;

			case SDLK_ESCAPE:
				gameRunning = false;
				break;
			}
			break;

		//Once key being pressed is stopped the input for specified key is cancelled
		case SDL_KEYUP:

			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				keyState &= (~Keys::Up);
				break;

			case SDLK_DOWN:
				keyState &= (~Keys::Down);
				break;

			case SDLK_LEFT:
				keyState &= (~Keys::Left);
				break;

			case SDLK_RIGHT:
				keyState &= (~Keys::Right);
				break;

			case SDLK_SPACE:
				keyState &= (~Keys::Fire);

				// Find first "free" bullet
				if (1) {

					int i = 0;
					while (bullets[i] != nullptr && i < MAX_BULLETS) {
						i++;
					}

					if (i < MAX_BULLETS) {
						//creates new bullet for the player to fire upon keypress (SPACEBAR)
						bullets[i] = new BulletInstance();
						bullets[i]->initialise(bulletType, mainPlayer->getPosition(), Float2(0.0f, -200.0f));//-200.0f allows for the bullets to fire vertically upwards (+y axis)
					}
				}
				break;
			}
			break;


		
		//xbox and generic gamepad input (USE DS4 WINDOWS for Dualshock 4 input)
		case SDL_CONTROLLERDEVICEADDED:

			//checks if gamepad device is connected
			deviceID = event.cdevice.which;
			printf("Controller device %d added to system\n", deviceID);
		
			//4 controllers maximum
			if (deviceID >= 0 && deviceID < 4) {
				controllers[deviceID] = SDL_GameControllerOpen(deviceID);
			}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:

			//checks if gamepad device is disconnected
			instanceID = event.cdevice.which;
			printf("Controller instance_id %d removed\n", instanceID);
		
			if (1) {

				SDL_GameController *controller = SDL_GameControllerFromInstanceID(instanceID);

				if (controller != nullptr) {

					SDL_GameControllerClose(controller);
				}
			}
			break;

			//gamepad axis motion, deadzone, and acceleration
		case SDL_CONTROLLERAXISMOTION:

			instanceID = event.caxis.which;

			if (instanceID == 0) {

				// mainPlayer only updated by controller with instanceID = 0
				Uint8 axisID = event.caxis.axis;

				//DeadZone (KEEP AT 7849)
				const Sint16 deadZone = 7849;

				switch (axisID) {

				case SDL_CONTROLLER_AXIS_LEFTX:
					lx = (abs(event.caxis.value) < deadZone) ? 0 : event.caxis.value;
					break;

				case SDL_CONTROLLER_AXIS_LEFTY:
					ly = (abs(event.caxis.value) < deadZone) ? 0 : event.caxis.value;
					break;
				}
			}
			break;

		case SDL_CONTROLLERBUTTONDOWN:

			instanceID = event.cbutton.which;

			if (instanceID == 0) {

				//Find first "free" bullet
				int i = 0;
				while (bullets[i] != nullptr && i < MAX_BULLETS) {
					i++;
				}

				if (i < MAX_BULLETS) {
					//creates new bullet for the player to fire upon buttonpress (general gamepad buttons X, A, B, Y or Square, Cross, Circle, Triangle)
					bullets[i] = new BulletInstance();
					bullets[i]->initialise(bulletType, mainPlayer->getPosition(), Float2(0.0f, -200.0f));
				}
			}
			break;

		case SDL_CONTROLLERBUTTONUP:

			instanceID = event.cbutton.which;

			if (instanceID == 0) {

				printf("id:%d button:%d status:%d\n", instanceID, event.cbutton.button, event.cbutton.state);
			}

			break;
		}
	}
}

//start of gameUpdate()
void SDLGame::update() {

	//player movement keyflags
	float xMovement = 0.0f;
	float yMovement = 0.0f;
	float rotation = 0.0f;

	//controller state
	if (lx != 0 || ly != 0 || rx != 0) {
		
		xMovement = float(lx) / 75000.0f * 100.0f;
		yMovement = float(ly) / 75000.0f * 100.0f;
		rotation = float(rx) / 32768.0f * (360.0f / 60.0f);
	}
	else {

		if (keyState & Keys::Left)
			xMovement = -200.0f;
		else if (keyState & Keys::Right)
			xMovement = 200.0f;

		if (keyState & Keys::Up)
			yMovement = -200.0f;
		else if (keyState & Keys::Down)
			yMovement = 200.0f;

		//Ensure length of direction vector is consistent for axis-aligned and diagonal movement
		float dx = float(xMovement);
		float dy = float(yMovement);

		float dLength = sqrtf(dx * dx + dy * dy);

		if (dLength > 0.0f) {

			dx = dx / dLength;
			dy = dy / dLength;

			dx *= 100.0f;
			dy *= 150.0f;//made the y axis movement faster due to the vehicle being a form of aircraft 

			xMovement = dx;
			yMovement = dy;
		}
	}

	mainPlayer->move(xMovement * timeDeltaInSeconds, yMovement * timeDeltaInSeconds);
	mainPlayer->rotate(rotation * timeDeltaInSeconds);

	//enemy update
	//float xMovement = 0.0f;
	//float yMovement = 100.0f;
	//enemySprite->move(xMovement * timeDeltaInSeconds, yMovement * timeDeltaInSeconds);
	
	//!!!!!!!!!!!
	//attempt to make enemy move however code in the update works different to how the player moves, as the player uses keypress if statements whereas the enemy should move on its own

	//bullet update
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			bullets[i]->update(timeDeltaInSeconds);
		}
	}

	//collision checks

	// Simple check between two objects
	if (AABB::intersectAABB(mainPlayer->getBoundingBox(), enemySprite->getBoundingBox())) {

		//When player is hit/touches enemy (checks health condition)
		mainPlayer->addHealth(-100.0f); //when player touches enemy = instant death and closes SDL game

		if (mainPlayer->getHealth() <= 0.0f) {

			printf("GAME OVER! TRY AGAIN!\n");
			gameRunning = false;
		}
	}

	//Projectile/Bullet Collision with Enemy
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			if (AABB::intersectAABB(bullets[i]->getBoundingBox(), enemySprite->getBoundingBox())) {

				//printf("enemy hit!\n");
				bullets[i]->hit(enemySprite);
				
				if (enemySprite->getHealth() <= 0.0f) {
					printf("+1 points awarded to player!\n");
					mainPlayer->addPoints(1.0f);
					
				}
					
			}
		}
	}
	
	// Recipe 9 - Check for bullets out of range - delete when found
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i] && bullets[i]->exceededRange()) {

			delete bullets[i];
			bullets[i] = nullptr;
		}
	}


}
//end of gameUpdate()

//start of draw()
void SDLGame::draw() {
	//all game content will be drawn on to the gameWindow from here

	//Screen Clear
	SDL_SetRenderDrawColor(gameRenderer, 0, 5, 255, 255); //RGBA
	SDL_RenderClear(gameRenderer);


	//Final steps of initialising SDL Game Window and Drawing Game Content

	//draw player
	mainPlayer->draw(gameRenderer);
	
	//draw enemy
	enemySprite->draw(gameRenderer);

	pickupSprite->draw(gameRenderer);

	//draw bullets
	for (int i = 0; i < MAX_BULLETS; i++) {

		if (bullets[i]) {
			bullets[i]->draw(gameRenderer);
		}
	}
	//shows current frame on screen
	SDL_RenderPresent(gameRenderer);
}
//end of draw()

//END OF GAMELOOP