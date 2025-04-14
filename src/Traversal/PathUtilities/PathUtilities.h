#pragma once
#include "../../Graph/Position.h"

struct PathUtilities
{
    static int ManhattanDist(Position* p1, Position* p2);
};

inline int PathUtilities::ManhattanDist(Position* p1, Position* p2)
{
    return std::abs(p1->x - p2->x) + std::abs(p1->y - p2->y);
}