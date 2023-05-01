#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>

void loadTextures();

void createTexture(SDL_Texture* &tex, const char* root);

void deleteTextures();