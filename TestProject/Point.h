#pragma once
struct Point
{
	float x, y;
};

Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);
Point operator*(const Point&, float);