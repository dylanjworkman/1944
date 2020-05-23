#pragma once

// Struct to model point (or direction) in 2D space

struct Float2 {

	float	x;
	float	y;

	Float2() {

		x = 0.0f;
		y = 0.0f;
	}

	Float2(float init_x, float init_y) {

		x = init_x;
		y = init_y;
	}
};