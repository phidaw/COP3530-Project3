#pragma once
#include <string>

struct Position
{
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& out, const Position* pos)
    {
        out << "(" + std::to_string(pos->x) + ", " + std::to_string(pos->y) + ")";
        return out;
    }
};