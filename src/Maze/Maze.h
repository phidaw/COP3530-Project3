#pragma once
#include <unordered_set>
#include <unordered_map>
#include "../Graph/Graph.h"
#include "../Graph/Edge.h"
#include "Prim.h"
#include "../Tools/Random/Random.h"

using std::unordered_map;
using std::unordered_set;

struct Maze
{
    const static int DEFAULT_NUM_CELLS = 16;
    const static int DEFAULT_MIN_WEIGHT = 1;
    const static int DEFAULT_MAX_WEIGHT = 30;

    Random rand;
    Graph graph;
    Cell* start;
    Cell* end;
    unordered_set<Edge*> walls;

    /**
     * Walls of maze are all graph edges, except for the set of edges produced by Prim's algorithm.
     * Since Prim's algorithm produces a spanning tree, there will a path connecting all cells in the graph.
     * Therefore, we can choose any two edges along outer border for entry and exit of the maze
     */
    void CreateEntrances()
    {
        // get random indices
        int startIndex = rand(0, graph.cells.Width()-1);
        int endIndex = rand(0, graph.cells.Width()-1);

        // assign start and end cells
        start = graph.cells.at(startIndex, 0);
        end = graph.cells.at(endIndex, graph.cells.Height()-1);

        // get top edge of a random node along top-outer boundary
        Edge* entryEdge = start->edges[Cell::CardinalDir::North];
        // get bottom edge of a random node along bot-outer boundary
        Edge* exitEdge = end->edges[Cell::CardinalDir::South];

        // erase two edges for entry and exit of maze
        walls.erase(entryEdge);
        walls.erase(exitEdge);
    }

    Maze(int numOfCells = DEFAULT_NUM_CELLS, int minWeight = DEFAULT_MIN_WEIGHT, int maxWeight = DEFAULT_MAX_WEIGHT)
        : rand(minWeight, maxWeight), graph(numOfCells), walls(Prim::CreateMaze(graph))
    {
        start = nullptr;
        end = nullptr;
        CreateEntrances();
    }

    // check if conjoining edge is within maze's walls
    // if not, then there's a path between cells
    bool CheckIfBlocked(Cell* from, Cell* to) const
    {
        Edge* edge = from->GetSharedEdge(to);
        if (edge && walls.count(edge) != 0)
            return true;

        return false;
    }
};