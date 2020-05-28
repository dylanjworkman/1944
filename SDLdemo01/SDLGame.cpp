#include "pch.h"
#include "SDLGame.h"


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
//start of initialisation
void SDLGame::initialise() {

	const int SDL_OKAY = 0;

	int sdlStatus = SDL_Init(SDL_INIT_EVERYTHING);

	if (sdlStatus != SDL_OKAY)
		throw "SDL init error";

	gameWindow = SDL_CreateWindow(
		"1944",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		600,
		SDL_WINDOW_SHOWN);

	// Enumerate render drivers
	int n = SDL_GetNumRenderDrivers();

	printf("Number of renderers = %d\n", n);

	for (int i = 0; i < n; ++i) {

		SDL_RendererInfo renderInfo;

		if (SDL_GetRenderDriverInfo(i, &renderInfo) == 0) { // 0 means success

			printf("Renderer %d : %s\n", i, renderInfo.name);
		}
	}

	// Use first (Default) renderer - this is usually Direct3D based
	gameRenderer = SDL_CreateRenderer(gameWindow, 0, 0);

	// -----------------------

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

	// Add other initialisation code here...


}//end of initialisation

//start of gameloop
void SDLGame::runGameLoop() {

	gameRunning = true;

	while (gameRunning) {

		// Recipe 3 - Update timing / clock
		
		// Calculate time elapsed
		currentTimeIndex = SDL_GetTicks();
		timeDelta = currentTimeIndex - prevTimeIndex;
		timeDeltaInSeconds = float(timeDelta) / 1000.0f;

		// Store current time index into prevTimeIndex for next frame
		prevTimeIndex = currentTimeIndex;

		// --------------------

		handleEvents();
		update();
		draw();
	}
}

void SDLGame::handleEvents() {

	SDL_Event event;

	// Recipe 4 - device and instance id variables for controller connections / removal
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

		// Once key being pressed is stopped the input for specified key is cancelled
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

						bullets[i] = new BulletInstance();
						bullets[i]->initialise(bulletType, mainPlayer->getPosition(), Float2(0.0f, -200.0f));//-200.0f allows for the bullets to fire vertically upwards (+y axis)
					}
				}

				break;
			}

			break;


		
		// xbox/generic gamepad input
		case SDL_CONTROLLERDEVICEADDED:

			deviceID = event.cdevice.which;
			printf("Controller device %d added to system\n", deviceID);
		
			// 4 controllers max
			if (deviceID >= 0 && deviceID < 4) {

				// Open controller for processing - deviceID indexes the ith controller on the system
				controllers[deviceID] = SDL_GameControllerOpen(deviceID);
			}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:

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

				// Implement "Dead Zone" of 7849 to avoid analogue noise creating suprious movement
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

				// Find first "free" bullet
				int i = 0;
				while (bullets[i] != nullptr && i < MAX_BULLETS) {
					i++;
				}

				if (i < MAX_BULLETS) {

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
			xMovement = -100.0f;
		else if (keyState & Keys::Right)
			xMovement = 100.0f;

		if (keyState & Keys::Up)
			yMovement = -100.0f;
		else if (keyState & Keys::Down)
			yMovement = 100.0f;

		// Ensure length of direction vector is consistent for axis-aligned and diagonal movement
		float dx = float(xMovement);
		float dy = float(yMovement);

		float dLength = sqrtf(dx * dx + dy * dy);

		if (dLength > 0.0f) {

			dx = dx / dLength;
			dy = dy / dLength;

			dx *= 100.0f;
			dy *= 100.0f;

			xMovement = dx;
			yMovement = dy;
		}
	}

	mainPlayer->move(xMovement * timeDeltaInSeconds, yMovement * timeDeltaInSeconds);
	mainPlayer->rotate(rotation * timeDeltaInSeconds);

	//enemy update


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

void SDLGame::draw() {

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
//end of gameloop