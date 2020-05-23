#pragma once

#include "ProjectileType.h"
#include "Float2.h"
#include "AABB.h"

class BulletInstance {

	ProjectileType*	type; // Provide access to sprite and damage

	Float2			pos; // Position
	Float2			vel; // Direction of travel (serves as velocity)

	float			distanceTravelled; // How far the bullet has travelled

	// Bounding volume for collisions
	AABB			boundingBox;

public:
	BulletInstance();
	~BulletInstance();

	// ProjectileInstance interface
	void initialise(ProjectileType* type, Float2 initPos, Float2 initVel);

	void update(float tDelta);
	void hit(Enemy* target);
	bool exceededRange();

	AABB getBoundingBox();

	void draw(SDL_Renderer* renderer);
};

