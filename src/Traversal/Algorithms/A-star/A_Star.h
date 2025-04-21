#pragma once
#include <vector>
#include <unordered_map>
#include "../../../Graph/Cell.h"
#include "../../../Maze/Maze.h"
#include "../../../Tools/Array2D/CellArray2D.h"

using std::vector;
using std::unordered_map;

class A_Star
{
    static Cell* Search(Maze& maze, Cell* start, Cell* end,
        unordered_map<Cell*, Cell*>& cameFrom, const int pathLimit);
public:
    static vector<Cell*> FindPath(Maze& maze, Cell* start, Cell* end, bool limitPath = false);
};