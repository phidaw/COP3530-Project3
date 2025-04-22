#pragma once
#include <vector>
#include <unordered_map>
#include "../../Graph/Cell.h"
#include "../../Maze/Maze.h"

using std::vector;
using std::unordered_map;

class BFS
{
    static Cell* Search(Maze& maze, Cell* start, Cell* end,
                        unordered_map<Cell*, Cell*>& cameFrom);
public:
    static vector<Cell*> FindPath(Maze& maze, Cell* start, Cell* end);
};