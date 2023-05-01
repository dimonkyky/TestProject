#pragma once
#include "Useful.h"
#include "TextureManager.h"

class Actor
{
protected:
	SDL_Texture* texture;
	SDL_Rect textureRectangle;
	int textureWidth;
	int textureHeight;
	Point position;

	float rotationAngle;

public:
	Actor(Point pPosition, int width, int height, SDL_Texture* texturePointer);

	virtual ~Actor();

	void draw();
};

