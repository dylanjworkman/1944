#include "pch.h"
#include "Enemy.h"
#include <array>

Enemy::Enemy()
{
	this->sprite = nullptr;
}


Enemy::~Enemy()
{
	delete sprite;
	this->sprite = nullptr;
}


void Enemy::initialise(Sprite* sprite, float initX, float initY) {

	x = initX;
	y = initY;

	this->sprite = sprite;

	//sprite size
	w = 64.0f;
	h = 64.0f;

	//Temp variables to calculate the centre point of the sprite given (x, y) are the top left
	float cx = x + (w / 2.0f);
	float cy = y + (h / 2.0f);

	boundingBox = AABB(cx, cy, w / 2.0f, h / 2.0f); //Store half w, h in the bounding box!
}

void Enemy::update() {
	
}

void Enemy::draw(SDL_Renderer* renderer) {

	SDL_Rect targetRect;

	targetRect.x = int(x);
	targetRect.y = int(y);
	targetRect.w = int(w);
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, 180.0f);

	boundingBox.draw(renderer);
}


void Enemy::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	boundingBox.move(xMovement, yMovement);//moves bounding box
}


//add health contents for the enemy sprite in-game
void Enemy::addHealth(int amountToAdd) {

	health += amountToAdd;
	printf("hit! enemy health = %d\n", health);
}

//looks for enemy's current health status
float Enemy::getHealth() {
	return health;
}

//checks for enemy sprite boundingbox 
AABB Enemy::getBoundingBox() {

	return boundingBox;
}

