#ifndef SPAWNPOSITION_H_
#define SPAWNPOSITION_H_

#include "pch.h"

struct SpawnPosition {
	float farLeft = 0.0f;
	float left = 0.0f;
	float center = 0.0f;
	float right = 0.0f;
	float farRight = 0.0f;

	SpawnPosition(SDL_Renderer* renderer) {
		int screenX = 0;
		int screenY = 0;

		SDL_GetRendererOutputSize(renderer, &screenX, &screenY);

		farLeft = float(32);
		left = float(screenX * 0.25f + 32);
		center = float(screenX * 0.5f);
		right = float(screenX * 0.75f - 32);
		farRight = float(screenX - 32);
	}
};
#endif /* SPAWNPOSITION_H_ */
