#pragma once

#include "Sprite.h"
#include "ProjectileType.h"
#include "Enemy.h"

class ProjectileInstance {

protected:

	

public:

	ProjectileInstance();
	virtual ~ProjectileInstance();

	virtual void initialise(ProjectileType* type, Float2 initPos, Float2 initVel) = 0;
	virtual void update(float tDelta) = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;

	virtual void hit(Enemy* target) = 0;

	virtual AABB getBoundingBox() = 0;
};
