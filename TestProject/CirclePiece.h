#pragma once
#include "Point.h"
#include "TextureManager.h"

struct CirclePiece
{
	SDL_FPoint position;
	SDL_FPoint secondaryPosition;
	float width;
	float stiffness;
	float deviationAngle;

	float radius;
	Point hitboxCenter;

	float speed;

	float shift;
	float lastShift;
	Point shiftVector;

	CirclePiece(SDL_FPoint pPosition, SDL_FPoint pSecondaryPosition, float pWidth, float pDeviationAngle, float pStiffness);
	
};

