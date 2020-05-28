#include "Sprite.h"
#include "Float2.h"
#include "AABB.h"
#include "pch.h"

class Pickup {
private:
	Sprite* sprite = nullptr;

	float x = 0.0f;
	float y = 0.0f;

	//bounding box
	float w = 0.0f;
	float h = 0.0f;
	AABB boundingBox;

	//pickup health duration
	int				health = 100;

public:
	Pickup();
	~Pickup();
	void initialise(Sprite* playerSprite, float initX, float initY);
	void update();
	void draw(SDL_Renderer* renderer);
	void move(float xMovement, float yMovement);
	void addHealth(int amountToAdd);
	float getHealth();
	AABB getBoundingBox();
};