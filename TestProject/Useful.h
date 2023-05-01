#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <SDL_image.h>
#include <cmath>
#include "Point.h"

#define LOG(X) std::cout<<X<<std::endl
#define PI 3.14159265359
#define TO_RADIANS(X) (X * PI / 180);

#define PRESSED true
#define RELEASED false

#define ROTATION_SLOWDOWN 0.1

float calculateDistanceBetweenPoints(Point p1, Point p2);

float cosAngleBetweenVectors(Point vec1, Point vec2);

float vectorLength(Point vec);

bool angleAcuteOrObtuse(Point vec1, Point vec2);

float dotToLineDistance(Point dot, Point lineP1, Point lineP2);

float min(float n1, float n2);

bool circleCollidedWithLine(float radius, Point center, Point lineP1, Point lineP2);

Point calculateMovementVector(Point position, Point destination);

float calculateRotationAngle(Point destination, Point position);