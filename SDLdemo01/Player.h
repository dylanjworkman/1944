#pragma once

#include "Sprite.h"
#include "Float2.h"
#include "AABB.h"

class Player
{
private:

	// Position
	float			x;
	float			y;
	float			orientation; // Recipe 4 - player can now be rotated - store angle of rotation in degrees

	Sprite*			sprite = nullptr;

	// Recipe 5 - new attributes for bounding volume...
	float			w;
	float			h;
	AABB			boundingBox;
	
	// Recipe 7 - points
	int				points;

	// Recipe 8 - health
	float			health;

public:
	Player();
	~Player();

	void initialise(Sprite* playerSprite, float initX, float initY, float initHealth);
	void update();
	void draw(SDL_Renderer* renderer);

	Float2 getPosition();
	void move(float xMovement, float yMovement);

	// Recipe 4 - player can now be rotated
	void rotate(float dTheta);

	// Recipe 6 - Add AABB accessor
	AABB getBoundingBox();

	// Recipe 7 - Update player's points / score by amountToAdd
	void addPoints(int amountToAdd);

	// Recipe 8 - Update health by amountToAdd (if amountToAdd is negative the player's health goes down!)
	void addHealth(float amountToAdd);
	float getHealth();
};


