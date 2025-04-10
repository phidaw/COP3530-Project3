#pragma once
#include "Position.h"

class Edge
{
public:
    enum Direction { Horizontal, Vertical };
    Position* v1;
    Position* v2;
    int weight;

    Direction GetDirection() const { return direction; }
    virtual ~Edge() = 0;
protected:
    Direction direction;
};
inline Edge::~Edge()
{}

struct HorizontalEdge : public Edge
{
    // v1 is Left, v2 is right
    HorizontalEdge(Position* v1, Position* v2)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->direction = Direction::Horizontal;
    }
};

struct VerticalEdge : public Edge
{
    // v1 is top, v2 is bot
    VerticalEdge(Position* v1, Position* v2)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->direction = Direction::Vertical;
    }
};