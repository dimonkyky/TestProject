#include "Actor.h"
extern SDL_Renderer* renderer;
extern float scaleX;
extern float scaleY;

Actor::Actor(Point pPosition, int width, int height, SDL_Texture* pTexture) 
    : position(pPosition), textureWidth(width), textureHeight(height), texture(pTexture)
{
    textureRectangle = {int(position.x) - width / 2, int(position.y) - height / 2, textureWidth, textureHeight };

    rotationAngle = 0;
}

Actor::~Actor() {
}

void Actor::draw() {
    SDL_Rect scaledRectangle = { textureRectangle.x * scaleX, textureRectangle.y * scaleY, textureRectangle.w * scaleX, textureRectangle.h * scaleY };
    SDL_RenderCopyEx(renderer, texture, NULL, &scaledRectangle, rotationAngle, NULL, SDL_FLIP_NONE);
}