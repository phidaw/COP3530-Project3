#pragma once
#include <vector>
#include <unordered_map>
#include "../../Graph/Cell.h"
#include "../../Maze/Maze.h"

using std::vector;
using std::unordered_map;

class Dijkstra
{
    static Cell* Search(Maze& maze, Cell* start, const vector<Cell*>& targets,
                        unordered_map<Cell*, Cell*>& cameFrom, unordered_map<Cell*, int>& costSoFar);
public:
    static vector<Cell*> FindPath(Maze& maze, Cell* start, const vector<Cell*>& targets);
};