#pragma once
#include <unordered_set>
#include <vector>
#include "../Graph/Graph.h"
#include "../Graph/Edge.h"
#include "../Graph/Cell.h"
#include "../Tools/Random/Random.h"

using std::unordered_set;
using std::vector;

struct Prim
{
    static Random rand;

    static void GetNeighbors(Cell* frontierCell, vector<Cell*>& visitedNeighbors,
        vector<Cell*>& frontier, unordered_set<Cell*> visited);

    static Cell* SelectRandomNeighbor(vector<Cell*>& visitedNeighbors);

    // produces a non-uniform min. span. tree of graph's edges
    static unordered_set<Edge*> CreateMaze(Graph& graph);
};