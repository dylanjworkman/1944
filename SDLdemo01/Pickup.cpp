#include "pch.h"
#include "Enemy.h"
#include "Pickup.h"
#include <array>

Pickup::Pickup() {

}

Pickup::~Pickup() {

}

void Pickup::initialise(Sprite* sprite, float initX, float initY) {
	this->sprite = sprite;
	w = 64.0f;
	h = 64.0f;

	float cx = x + (w / 2.0f);
	float cy = y + (h / 2.0f);

	boundingBox = AABB(cx, cy, w / 2.0f, h / 2.0f);
}

void Pickup::update() {

}

void Pickup::draw(SDL_Renderer* renderer) {

	SDL_Rect targetRect;

	targetRect.x = int(x);
	targetRect.y = int(y);
	targetRect.w = int(w);
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, 180.0f);

	boundingBox.draw(renderer);
}

void Pickup::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	boundingBox.move(xMovement, yMovement);
}

void Pickup::addHealth(int amountToAdd) {

	health += amountToAdd;
}
float Pickup::getHealth() {
	return health;
}
AABB Pickup::getBoundingBox() {

	return boundingBox;
}