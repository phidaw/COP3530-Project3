#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "../Graph/Cell.h"
#include "../Graph/Graph.h"
#include "../Graph/Edge.h"
#include "Prim.h"
#include "../Tools/Random/Random.h"

#define DEBUG_MODE false

using std::unordered_map;
using std::unordered_set;
using std::vector;

// redeclare static variable
Random Prim::rand;

void Prim::GetNeighbors(Cell* frontierCell, vector<Cell*>& visitedNeighbors,
    vector<Cell*>& frontier, unordered_set<Cell*> visited)
{
    for (Cell* neighbor : frontierCell->adjacentCells)
    {
        if (!neighbor) continue;

        if (visited.find(neighbor) != visited.end())
            visitedNeighbors.push_back(neighbor);
        else if (!neighbor->discovered)
        {
            // add non-visited, undiscovered neighbor to frontier
            neighbor->discovered = true;
            frontier.push_back(neighbor);
        }
    }
}
Cell* Prim::SelectRandomNeighbor(vector<Cell*>& visitedNeighbors)
{
    Cell* inNeighbor;
    if (visitedNeighbors.size() == 1)
        inNeighbor = visitedNeighbors[0];
    else
        inNeighbor = visitedNeighbors[rand(0, visitedNeighbors.size()-1, DEBUG_MODE)];

    return inNeighbor;
}

/**
 * choose an arbitrary vertex from Graph, G, and add it to some (initially empty) visited set, S.
 * while |S| != |G|
     * select a random edge that connects a vertex in S with another not in S.
     * add that edge to the spanning tree, and the edge's vertex not in S to S.
 */
unordered_set<Edge*> Prim::CreateMaze(Graph& graph)
{
    // change bounds of distribution to range of cells per row/col of graph
    rand.ChangeBounds(0, graph.GetCellsPerRow()-1);

    unordered_set<Edge*> maze(graph.edges);
    unordered_set<Cell*> visited { graph.cells.at(rand(DEBUG_MODE), rand(DEBUG_MODE)) };
    vector<Cell*> frontier;

    // add neighbors of starting cell to frontier
    for (Cell* neighbor : (*visited.begin())->adjacentCells)
    {
        if (neighbor)
        {
            neighbor->discovered = true;
            frontier.push_back(neighbor);
        }
    }

    while (!frontier.empty())
    {
        // select random cell from frontier
        const int cellIndex = rand(0, frontier.size()-1, DEBUG_MODE);
        Cell* frontierCell = frontier[cellIndex];

        // get cell's visited neighbors and add unvisited ones to frontier
        vector<Cell*> visitedNeighbors;
        GetNeighbors(frontierCell, visitedNeighbors, frontier, visited);

        // select random visited neighbor
        Cell* inNeighbor = SelectRandomNeighbor(visitedNeighbors);

        // carve passage
        maze.erase(Graph::GetSharedEdge(frontierCell, inNeighbor));

        // remove cell from frontier (can be done "out of order")
        std::swap(frontier[cellIndex], frontier[frontier.size()-1]);
        frontier.pop_back();

        // add cell to visited (can be done "out of order")
        visited.emplace(frontierCell);
    }

    // maze consists of all edges from graph excluding those that comprise MST
    return maze;
}