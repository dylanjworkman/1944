#include "pch.h"
#include "Sprite.h"


Sprite::Sprite() {
	// Duplicated form header
	texture = nullptr;
}


Sprite::~Sprite() {
	// Did someone say deallocation?
}


void Sprite::initialise(SDL_Renderer* renderer, const char *pathToImage) {

	//Load image, allows path to be set to a specified directory and image
	SDL_Surface* image = IMG_Load(pathToImage);

	//Creates texture from loaded image
	texture = SDL_CreateTextureFromSurface(renderer, image);

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	SDL_QueryTexture(texture, 0, 0, &(sourceRectangle.w), &(sourceRectangle.h));

	// Clean-up - we're done with 'image' now our texture has been created
	SDL_FreeSurface(image);
}

void Sprite::draw(SDL_Renderer* renderer, SDL_Rect* targetRect, float renderOrientation) {

	SDL_RenderCopyEx(renderer, texture, &sourceRectangle, targetRect, renderOrientation, 0, SDL_FLIP_NONE);
}