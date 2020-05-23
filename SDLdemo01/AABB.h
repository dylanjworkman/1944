#pragma once

// Recipe 5 - Axis Aligned Bounding Box for collision detection

#include "Float2.h"

struct AABB {

	static bool intersectAABB(AABB A, AABB B) {

		return (fabs(A.pos.x - B.pos.x) < (A.w + B.w) &&
				fabs(A.pos.y - B.pos.y) < (A.h + B.h));
	}


	// Centre point of AABB
	Float2		pos;
	
	// Half-width and half-height of the AABB
	float		w;
	float		h;

	AABB() {

		pos = Float2();
		w = 0.0f;
		h = 0.0f;
	}

	AABB(float init_x, float init_y, float init_w, float init_h) {

		pos = Float2(init_x, init_y);

		w = init_w;
		h = init_h;
	}

	AABB(Float2 init_pos, float init_w, float init_h) {

		pos = init_pos;

		w = init_w;
		h = init_h;
	}

	void move(float dx, float dy) {

		pos.x += dx;
		pos.y += dy;
	}
	
	void draw(SDL_Renderer* renderer) {

		SDL_Rect targetRect;

		targetRect.x = int(pos.x - w);
		targetRect.y = int(pos.y - h);
		targetRect.w = int(w * 2.0f);
		targetRect.h = int(h * 2.0f);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &targetRect);
	}
};