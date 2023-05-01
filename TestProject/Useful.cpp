#include "Useful.h"

float calculateDistanceBetweenPoints(Point p1, Point p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

float cosAngleBetweenVectors(Point vec1, Point vec2)
{
    return ((vec1.x * vec2.x) + (vec1.y * vec2.y)) / (sqrt(vec1.x * vec1.x + vec1.y * vec1.y) * sqrt(vec2.x * vec2.x + vec2.y * vec2.y));
}

float vectorLength(Point vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

bool angleAcuteOrObtuse(Point vec1, Point vec2)
{
    if ((vec1.x * vec2.x + vec1.y * vec2.y) >= 0) {
        return 1;
    }
    return 0;
}

float dotToLineDistance(Point dot, Point lineP1, Point lineP2)
{
    Point lineVec1 = { lineP2.x - lineP1.x, lineP2.y - lineP1.y };
    Point lineVec2 = { lineP1.x - lineP2.x, lineP1.y - lineP2.y };
    Point dotVec1 = { dot.x - lineP1.x, dot.y - lineP1.y };
    Point dotVec2 = { dot.x - lineP2.x, dot.y - lineP2.y };
    if (angleAcuteOrObtuse(dotVec1, lineVec1) == 1 && angleAcuteOrObtuse(dotVec2, lineVec2) == 1) {
        // line | Ax + By + C = 0
        float A = (lineP2.y - lineP1.y);
        float B = (lineP2.x - lineP1.x);
        float C = (lineP2.x * lineP1.y) - (lineP1.x * lineP2.y);

        return fabs(A * dot.x + B * (-dot.y) + C) / sqrt(A * A + B * B);
    }
    else {
        return min(calculateDistanceBetweenPoints(dot, lineP1), calculateDistanceBetweenPoints(dot, lineP2));
    }
}

float min(float n1, float n2)
{
    if (n1 <= n2) {
        return n1;
    }
    else {
        return n2;
    }
}

bool circleCollidedWithLine(float radius, Point center, Point lineP1, Point lineP2)
{
    if (dotToLineDistance(center, lineP1, lineP2) > radius) {
        return 0;
    }
    return 1;

    /*if (calculateDistanceBetweenPoints(center, lineP1) <= radius || calculateDistanceBetweenPoints(center, lineP2) <= radius) {
        return 1;
    }
    if (fabs(lineP1.x - lineP2.x) >= fabs(lineP1.y - lineP2.y)) {
        if ((lineP2.x - lineP1.x >= 0) && (center.x >= lineP1.x) && (center.x <= lineP2.x)) {
            return 1;
        }
        if ((lineP2.x - lineP1.x < 0) && (center.x <= lineP1.x) && (center.x >= lineP2.x)) {
            return 1;
        }
    }
    else {
        if ((lineP2.y - lineP1.y >= 0) && (center.y >= lineP1.y) && (center.y <= lineP2.y)) {
            return 1;
        }
        if ((lineP2.y - lineP1.y < 0) && (center.y <= lineP1.y) && (center.y >= lineP2.y)) {
            return 1;
        }
    }*/
}

Point calculateMovementVector(Point position, Point destination)
{
    float cathetusX = destination.x - position.x;
    float cathetusY = destination.y - position.y;
    float hypotenuse = sqrt((cathetusX * cathetusX) + (cathetusY * cathetusY));
    if (cathetusX != 0 && cathetusY != 0) {
        return Point{ cathetusX / hypotenuse, cathetusY / hypotenuse };
    }
    else if (cathetusX == 0) {
        return Point{ 0, cathetusY / hypotenuse };
    }
    else if (cathetusY == 0) {
        return Point{ cathetusX / hypotenuse, 0 };
    }
}

float calculateRotationAngle(Point destination, Point position)
{
    return (atan2(float(destination.x - position.x), float(position.y - destination.y)) * 180 / 3.14);
}
