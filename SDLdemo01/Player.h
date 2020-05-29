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
	float			orientation;

	Sprite*			sprite = nullptr;

	//boundingbox volume
	float			w;
	float			h;
	AABB			boundingBox;
	
	//points
	int points = 0;

	//health
	float			health;

public:
	Player();
	~Player();

	void initialise(Sprite* playerSprite, float initX, float initY, float initHealth);
	void update();
	void draw(SDL_Renderer* renderer);

	Float2 getPosition();
	void move(float xMovement, float yMovement);

	//player rotation
	void rotate(float dTheta);

	//AABB accessor
	AABB getBoundingBox();

	//add/update player points
	void addPoints(int amountToAdd);
	float getPoints();

	//add/update player health
	void addHealth(float amountToAdd);
	float getHealth();
};


