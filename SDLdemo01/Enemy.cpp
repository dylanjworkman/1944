#include "pch.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


void Enemy::initialise(Sprite* sprite, float initX, float initY) {

	x = initX;
	y = initY;

	this->sprite = sprite;

	// Recipe 5 - to define bounding box we need size of sprite in game world!
	w = 64.0f;
	h = 64.0f;

	// Temp variables to calculate the centre point of the sprite given (x, y) are the top left
	float cx = x + (w / 2.0f);
	float cy = y + (h / 2.0f);

	boundingBox = AABB(cx, cy, w / 2.0f, h / 2.0f); // Store half w, h in the bounding box!
}

void Enemy::update() {
}

void Enemy::draw(SDL_Renderer* renderer) {

	SDL_Rect targetRect;

	targetRect.x = int(x);
	targetRect.y = int(y);
	targetRect.w = int(w); // Recipe 5 - get size from attributes - no longer hard-coded values!
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, 180.0f);

	boundingBox.draw(renderer);
}


void Enemy::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	// Recipe 5 - move bounding box too!
	boundingBox.move(xMovement, yMovement);
}


// Recipe 9 - addHealth called when bullets hit with negative value for amountToAdd parameter
void Enemy::addHealth(int amountToAdd) {

	health += amountToAdd;
	printf("health = %d\n", health);
}

float Enemy::getHealth() {
	return health;
}

// Recipe 5 - Add AABB accessor so Game Object can get this information to test for collisions
// Note: GRASP dictates the Enemy class knows nothing about the Game Object - and it doesn't - but any caller can ask for the bounding box
AABB Enemy::getBoundingBox() {

	return boundingBox;
}

