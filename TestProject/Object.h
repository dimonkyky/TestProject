#pragma once
#include "Actor.h"
#include "Useful.h"

class Object :
    public Actor
{
    std::vector<Point> hitbox;
};

