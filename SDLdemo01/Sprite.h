#pragma once
class Sprite
{
private:

	SDL_Texture*	texture = nullptr;
	SDL_Rect		sourceRectangle;

public:
	Sprite();
	virtual ~Sprite();

	void initialise(SDL_Renderer* renderer, const char *pathToImage);
	void draw(SDL_Renderer* renderer, SDL_Rect* targetRect, float renderOrientation); // Recipe 4 - Add rotation to sprite rendering
};

