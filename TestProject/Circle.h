#pragma once
#include "Actor.h"
#include "Useful.h"
#include "TextureManager.h"
#include "CirclePiece.h"

class Circle :
    public Actor
{
private:
    float radius;
    float width;
    float stepDegree;

    int pieces;
    std::vector<CirclePiece> circlePieces;
    SDL_Texture* piecesTexture;

    Point lastPosition;
    float deltaDistance;

    Point movementVector;
    float speed;
    float acceleration;

    Point gravityVector;
    float airResistance;

    float rotationSpeed;

    float maxShift;
    Point maxShiftPieceShiftVector;
public:
    Circle(Point pPosition, SDL_Texture* texturePointer, SDL_Texture* pPiecesTexture, float pRadius, float speed, float pStiffness);
    void setSomeSettingsToDefault();

    float getRadius();
    Point getPosition();

    void drawPieces();

    void goUp(float tickTime);
    void goLeft(float tickTime);
    void goDown(float tickTime);
    void goRight(float tickTime);
    void move(float tickTime);

    void calculateRotationSpeed(float tickTime);
    void calculateRotationReaction(float tickTime, float deltaRotationSpeed, Point linePointVector);
    void rotate();
    void rotationSlowdown(float tickTime);
    void arrangeThePieces();

    void gravityEffect(float tickTime);
    void calculateAirResistance(float tickTime);

    void calculateCollisions(Point lineP1, Point lineP2);
    void calculatePiecesShiftVectors();
    void calculatePiecesResistance(float tickTime);

    void piecesShiftReset();
};

