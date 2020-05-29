#pragma once

#include "Sprite.h"
#include "AABB.h"
#include "Enemy.h"


class ProjectileType
{
	//projectile/bullet sprite
	Sprite*			sprite;

	// Damage
	float			damage;
	
	// Range
	float			range;

	//projectile/bullet dimensions
	float			w, h;

public:

	ProjectileType();
	virtual ~ProjectileType();

	void initialise(Sprite* playerSprite, float projectileDamage, float projectileRange, float width, float height);

	// Read-only accessors
	float getDamage();
	float getRange();
	float getWidth();
	float getHeight();

	void draw(SDL_Renderer* renderer, Float2 pos, float orientation);
};


