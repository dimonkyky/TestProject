#pragma once
#include "Useful.h"
#include "Circle.h"

class GameMap
{
private:
	std::vector<std::vector<Point>> *mapLayout;
	Circle *circle;

	std::vector<Point> linesCollidingCircle;

	bool circleCollidesWithMap;
public:
	GameMap(std::vector<std::vector<Point>>& pMapLayout, Circle &pCircle);

	void tick(float tickTime);
	void ProcessInput(float tickTime);
	void resetTickValues();
	void drawLayout();
	bool findCollisions();
	void callCollisionCalculations(float tickTime);
};

