#include "pch.h"
#include "Player.h"
#include "AABB.h"

Player::Player()
{
	// Good practice
	// if we try to use sprite before its allocated
	// we'll get a null ptr error. 
	this->sprite = nullptr;
}


Player::~Player()
{
	delete sprite;
	//Again good practice
	//deleted objects can be used
	//until they are overwritten!
	this->sprite = nullptr;
}


void Player::initialise(Sprite* sprite, float initX, float initY, float initHealth) {

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

	// Recipe 7 - Points
	points = 0;

	// Recipe 8 - Health
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

	// Recipe 5 - Draw AABB to show collision boundary
	boundingBox.draw(renderer);
}


Float2 Player::getPosition() {

	return Float2(x, y);
}


void Player::move(float xMovement, float yMovement) {

	x += xMovement;
	y += yMovement;

	// Recipe 5 - need to move bounding volume too!
	boundingBox.move(xMovement, yMovement);
}


// Recipe 4 - Add ability to rotate the player
void Player::rotate(float dTheta) {

	orientation += dTheta;

	// Note: Don't change AABB - this is ALWAYS axis aligned!
}


// Recipe 5 - AABB accessor
AABB Player::getBoundingBox() {

	return boundingBox;
}


// Recipe 7 - Update player's points / score by amountToAdd
void Player::addPoints(int amountToAdd) {

	points += amountToAdd;
}


// Recipe 8 - Update health by amountToAdd (if amountToAdd is negative the player's health goes down!)
void Player::addHealth(float amountToAdd) {

	health += amountToAdd;
	printf("health = %f\n", health);
}


float Player::getHealth() {

	return health;
}