#pragma once
#include "Position.h"

class Edge
{
public:
    enum Direction { Horizontal, Vertical };
    Position* v1;
    Position* v2;

    Edge(Position* v1, Position* v2, Direction direction) :
        v1(v1), v2(v2), direction(direction) {}

    Direction GetDirection() const { return direction; }
private:
    Direction direction;
};