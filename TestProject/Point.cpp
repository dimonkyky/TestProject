#include "Point.h"

Point operator+(const Point& p1, const Point& p2)
{
    return Point{ p1.x + p2.x, p1.y + p2.y };
}

Point operator-(const Point& p1, const Point& p2)
{
    return Point{ p1.x - p2.x, p1.y - p2.y };
}

Point operator*(const Point& p, float n)
{
    return Point{ p.x * n, p.y * n };
}
