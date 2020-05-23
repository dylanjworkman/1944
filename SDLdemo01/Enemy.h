#pragma once

// Enemy type for Recipe 5 (Collision Detection) and Recipe 9 (Bullets)

#include "Sprite.h"
#include "Float2.h"
#include "AABB.h"

class Enemy
{
private:

	// Position
	float			x;
	float			y;

	Sprite*			sprite;

	// Bounding box
	float			w;
	float			h;
	AABB			boundingBox;

	// Enemy health
	int				health = 100;

public:
	Enemy();
	~Enemy();

	void initialise(Sprite* playerSprite, float initX, float initY);
	void update();
	void draw(SDL_Renderer* renderer);

	void move(float xMovement, float yMovement);

	void addHealth(int amountToAdd);

	AABB getBoundingBox();
};

