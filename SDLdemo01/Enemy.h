#pragma once

// Enemy type for Recipe 5 (Collision Detection) and Recipe 9 (Bullets)

#include "Sprite.h"
#include "Float2.h"
#include "AABB.h"
#include "pch.h"

class Enemy
{
private:

	Sprite* sprite = nullptr;

	int id = -1;

	//move
	float x = 0.0f;
	float y = 0.0f;

	//bounding box
	float w = 0.0f;
	float h = 0.0f;
	AABB boundingBox;

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
	float getHealth();

	AABB getBoundingBox();
};

