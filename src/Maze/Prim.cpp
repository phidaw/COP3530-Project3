#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "../Graph/Cell.h"
#include "../Graph/Graph.h"
#include "../Graph/Edge.h"
#include "Prim.h"
#include "../Tools/Random/Random.h"

using std::unordered_map;
using std::unordered_set;
using std::vector;

// redeclare static variable
Random Prim::rand;

void Prim::GetNeighbors(Cell* frontierCell, vector<Cell*>& visitedNeighbors,
    vector<Cell*>& frontier, unordered_set<Cell*>& visited, int& fSize)
{
    for (int i = 0; i < Cell::numDir; i++)
    {
        Cell* neighbor = frontierCell->adjacentCells[i];

        if (!neighbor) continue;

        if (visited.find(neighbor) != visited.end())
            visitedNeighbors.push_back(neighbor);
        else if (!neighbor->discovered)
        {
            // add non-visited, undiscovered neighbor to frontier
            neighbor->discovered = true;
            frontier[fSize++] = neighbor;
        }
    }
}
Cell* Prim::SelectRandomNeighbor(vector<Cell*>& visitedNeighbors)
{
    Cell* inNeighbor;
    if (visitedNeighbors.size() == 1)
        inNeighbor = visitedNeighbors[0];
    else
        inNeighbor = visitedNeighbors[rand(0, visitedNeighbors.size()-1)];

    return inNeighbor;
}

unordered_set<Edge*> Prim::CreateMaze(Graph& graph)
{
    // change bounds of distribution to range of cells per row/col of graph
    rand.ChangeBounds(0, graph.GetCellsPerRow()-1);

    unordered_set<Edge*> maze(graph.edges);
    unordered_set<Cell*> visited { graph.cells.at(rand(), rand()) };
    vector<Cell*> frontier(graph.GetCellNum());

    // keep track of positions in frontier
    int fSize = 0;

    // add neighbors of starting cell to frontier
    for (Cell* neighbor : (*visited.begin())->adjacentCells)
    {
        if (neighbor)
        {
            neighbor->discovered = true;
            frontier[fSize++] = neighbor;
        }
    }

    while (visited.size() != graph.GetCellNum())
    {
        // select random cell from frontier
        const int cellIndex = rand(0, fSize-1);
        Cell* frontierCell = frontier[cellIndex];

        // remove cell from frontier
        // shift valid cells after frontierCell down (+1 null)
        int p = cellIndex-1;
        while (++p != fSize)
            frontier[p] = frontier[p+1];
        fSize--;

        // get cell's visited neighbors and add unvisited ones to frontier
        vector<Cell*> visitedNeighbors;
        GetNeighbors(frontierCell, visitedNeighbors, frontier, visited, fSize);

        // select random visited neighbor
        Cell* inNeighbor = SelectRandomNeighbor(visitedNeighbors);

        // carve passage
        maze.erase(frontierCell->GetSharedEdge(inNeighbor));

        // add cell to visited (can be done "out of order")
        visited.emplace(frontierCell);
    }

    // maze consists of all edges from graph excluding those that comprise MST
    return maze;
}