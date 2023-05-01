#include "TextureManager.h"

extern SDL_Renderer* renderer;
std::list<SDL_Texture*> textureList;

SDL_Texture* test1;
SDL_Texture* test2;
SDL_Texture* slizenTexture;
SDL_Texture* slizen_rad;

void loadTextures() {
    createTexture(test1, "resource/images/test1.jpg");
    createTexture(test2, "resource/images/test2.png");
    createTexture(slizenTexture, "resource/images/slizen_yellow.png");
    createTexture(slizen_rad, "resource/images/slizen_rad.png");
}


void createTexture(SDL_Texture * &tex, const char * root) {
    SDL_Surface* surface = IMG_Load(root);
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    textureList.push_back(tex);
    SDL_FreeSurface(surface);
}

void deleteTextures() {
    for (auto& texture : textureList)
    {
        SDL_DestroyTexture(texture);
    }
}