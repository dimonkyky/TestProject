#include <iostream>
#include "Useful.h"
#include "TextureManager.h"
#include "Circle.h"
#include "GameMap.h"

SDL_Renderer* renderer;

extern SDL_Texture* test1;
extern SDL_Texture* test2;
extern SDL_Texture* slizenTexture;
extern SDL_Texture* slizen_rad;

int targetFps = 432;

double globalTime;

int screenWidth = 1600;
int screenHeight = 900;

float scaleX;
float scaleY;

std::vector<bool> keyboard(255);

int main(int argc, char* args[])
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //getDisplaySize
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        screenWidth = DM.w;
        screenHeight = DM.h;

        scaleX = float(screenWidth) / 1600;
        scaleY = float(screenHeight) / 900;
        //create window
        window = SDL_CreateWindow("Aboltus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface(window);
        }
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    renderer = SDL_CreateRenderer(window, -1, render_flags);
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    globalTime = 0;
    double deltaTime = 0;
    double tickTime = 0;
    double fpsTime = 0;

    bool close = 0;
    int fps = 0;

    loadTextures();

    std::vector<Point> obj1 = { {900, 350}, {-100, 0}, {-100, 800}, {800, 800}, {820, 790}, {840, 800}, {1100, 800}, {1100, 300}, {1800, 300}, {1800, 150}, {1300, 150}, {1300, 0} };

    std::vector<Point> obj2 = { {350, 100}, {400, 100} };

    std::vector<std::vector<Point>> mapLayout = { obj1, obj2 };

    Point pos{400, 600};
    float r = 75;
    Circle circle{pos, slizen_rad, slizenTexture, r, 10, 1};

    GameMap testMap{mapLayout, circle};

    while (!close) {

        SDL_Event event;
        // Events management
        while (SDL_PollEvent(&event)) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            switch (event.type) {
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_MOUSEBUTTONDOWN:
                LOG("You clicked on : x = " << x << "; y = " << y);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym < 256) {
                    keyboard[event.key.keysym.sym] = PRESSED;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym < 256) {
                    keyboard[event.key.keysym.sym] = RELEASED;
                }
                break;
            }
            if (keyboard[SDLK_ESCAPE] == PRESSED) {
                close = 1;
            }
        }
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
        globalTime += deltaTime;
        fpsTime += deltaTime;

        tickTime += deltaTime;

        if (tickTime >= 1 / double(targetFps)) {
            testMap.tick(1 / double(targetFps));
            fps++;

            tickTime = 0;

        }

        //fps output
        /*if (fpsTime >= 1) {
            LOG(fps);
            fps = 0;
            fpsTime -= 1;
        }*/
    }

    deleteTextures();

    SDL_DestroyWindow(window);

    SDL_DestroyRenderer(renderer);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}