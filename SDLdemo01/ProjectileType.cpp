#include "pch.h"
#include "ProjectileType.h"


ProjectileType::ProjectileType()
{
}

ProjectileType::~ProjectileType()
{
}

void ProjectileType::initialise(Sprite* projectileSprite, float projectileDamage, float projectileRange, float width, float height) {

	sprite = projectileSprite;
	damage = projectileDamage;
	range = projectileRange;
	w = width;
	h = height;
}

float ProjectileType::getDamage() {

	return damage;
}

float ProjectileType::getRange() {

	return range;
}

float ProjectileType::getWidth() {
	
	return w;
}

float ProjectileType::getHeight() {

	return h;
}

void ProjectileType::draw(SDL_Renderer* renderer, Float2 pos, float orientation) {
	
	SDL_Rect targetRect;

	targetRect.x = int(pos.x);
	targetRect.y = int(pos.y);
	targetRect.w = int(w);
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, orientation);
}
