#include "pch.h"
#include "Player.h"
#include "AABB.h"

Player::Player()
{
	this->sprite = nullptr;
}


Player::~Player()
{
	delete sprite;
	this->sprite = nullptr;
}


void Player::initialise(Sprite* sprite, float initX, float initY, float initHealth) {

	x = initX;
	y = initY;

	this->sprite = sprite;

	//Sprite size
	w = 64.0f;
	h = 64.0f;

	//calculates centre point of sprite
	float cx = x + (w / 2.0f);
	float cy = y + (h / 2.0f);
	
	boundingBox = AABB(cx, cy, w / 2.0f, h / 2.0f); //centre points in bounding box for player sprite

	//player points
	points = 0;

	//player health initialise
	health = initHealth;
}


void Player::update() {
}


void Player::draw(SDL_Renderer* renderer) {

	SDL_Rect targetRect;

	targetRect.x = int(x);
	targetRect.y = int(y);
	targetRect.w = int(w);
	targetRect.h = int(h);

	sprite->draw(renderer, &targetRect, orientation);

	//draws bounding box into game
	boundingBox.draw(renderer);
}


Float2 Player::getPosition() {

	return Float2(x, y);
}

//x, y axis player movement
void Player::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	boundingBox.move(xMovement, yMovement);
}


//Player Rotation: Controller Only
void Player::rotate(float dTheta) {

	orientation += dTheta;
}


//bounding box accessor
AABB Player::getBoundingBox() {

	return boundingBox;
}


//player points updater
void Player::addPoints(int amountToAdd) {

	points += amountToAdd;
}

//checks for player points
float Player::getPoints() {
	return points;
}

//player health on launch of game
void Player::addHealth(float amountToAdd) {

	health += amountToAdd;
	printf("health = %f\n", health);
}

//returns information about player's current health
float Player::getHealth() {

	return health;
}