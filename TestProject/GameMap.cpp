#include "GameMap.h"
extern SDL_Renderer* renderer;
extern float scaleX;
extern float scaleY;
extern std::vector<bool> keyboard;

GameMap::GameMap(std::vector<std::vector<Point>>& pMapLayout, Circle& pCircle)
	: mapLayout(&pMapLayout), circle(&pCircle) 
{
    circleCollidesWithMap = 0;
    linesCollidingCircle.reserve(8);
}

void GameMap::tick(float tickTime)
{
    circle->gravityEffect(tickTime);
    circle->calculateAirResistance(tickTime);
    circle->move(tickTime);
    circle->rotate();
    circleCollidesWithMap = findCollisions();
    ProcessInput(tickTime);
    if (circleCollidesWithMap) {
        callCollisionCalculations(tickTime);
        circle->calculateRotationSpeed(tickTime);
    }
    else {
        circle->rotationSlowdown(tickTime);
    }

    SDL_RenderClear(renderer);
    drawLayout();
    circle->drawPieces();
    circle->draw();
    SDL_SetRenderDrawColor(renderer, 20, 200, 200, 255);
    SDL_RenderPresent(renderer);

    resetTickValues();
}

void GameMap::ProcessInput(float tickTime)
{
    if (circleCollidesWithMap) {
        if (keyboard[SDLK_w] == PRESSED) {
            circle->goUp(tickTime);
        }
        if (keyboard[SDLK_a] == PRESSED) {
            circle->goLeft(tickTime);
        }
        if (keyboard[SDLK_s] == PRESSED) {
            circle->goDown(tickTime);
        }
        if (keyboard[SDLK_d] == PRESSED) {
            circle->goRight(tickTime);
        }
    }
}

void GameMap::resetTickValues()
{
    circleCollidesWithMap = 0;
    linesCollidingCircle.clear();
    circle->piecesShiftReset();
}

void GameMap::drawLayout()
{
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    for (int i = 0; i < mapLayout->size(); i++) {
        for (int j = 0; j < mapLayout->at(i).size() - 1; j++) {
            SDL_RenderDrawLine(renderer, mapLayout->at(i)[j].x * scaleX, mapLayout->at(i)[j].y * scaleY, mapLayout->at(i)[j + 1].x * scaleX, mapLayout->at(i)[j + 1].y * scaleY);
        }
    }
}

bool GameMap::findCollisions()
{
    bool collides = 0;
    for (int i = 0; i < mapLayout->size(); i++) {
        for (int j = 0; j < mapLayout->at(i).size() - 1; j++) {
            if (circleCollidedWithLine(circle->getRadius(), circle->getPosition(), mapLayout->at(i)[j], mapLayout->at(i)[j + 1])) {
                linesCollidingCircle.emplace_back(mapLayout->at(i)[j]);
                linesCollidingCircle.emplace_back(mapLayout->at(i)[j + 1]);
                collides = 1;
            }
        }
    }
    return collides;
}

void GameMap::callCollisionCalculations(float tickTime)
{
    circle->calculatePiecesShiftVectors();
    for (int i = 0; i < linesCollidingCircle.size() - 1; i += 2) {
        circle->calculateCollisions(linesCollidingCircle[i], linesCollidingCircle[i + 1]);
    }
    circle->calculatePiecesResistance(tickTime);
    circle->arrangeThePieces();
}
