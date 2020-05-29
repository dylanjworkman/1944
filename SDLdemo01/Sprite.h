#pragma once
class Sprite
{
private:

	SDL_Texture*	texture = nullptr;
	SDL_Rect		sourceRectangle;

public:
	Sprite();
	virtual ~Sprite();
	//general sprite initialise and render
	void initialise(SDL_Renderer* renderer, const char *pathToImage);
	void draw(SDL_Renderer* renderer, SDL_Rect* targetRect, float renderOrientation);
};

