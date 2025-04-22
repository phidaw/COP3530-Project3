#include <unordered_map>
#include "../../Graph/Cell.h"
#include "../../Maze/Maze.h"
#include "../PathUtilities/PathUtilities.h"
#include "../../Tools/RadixHeap/RadixHeapDouble.h"
#include "Dijkstra.h"

using std::unordered_map;

Cell* Dijkstra::Search(Maze& maze, Cell* start, const vector<Cell*>& targets,
                       unordered_map<Cell*, Cell*>& cameFrom,
                       unordered_map<Cell*, int>& costSoFar)
{
    RadixHeapDouble frontier(maze.graph.GetCellNum());
    frontier.Insert(0, start);
    costSoFar[start] = 0;
    cameFrom[start] = start;

    // Track targets to find
    unordered_map<Cell*, bool> targetsFound;
    for (Cell* target : targets)
        targetsFound[target] = false;

    while (!frontier.Empty())
    {
        Cell* curr = frontier.ExtractMin();

        // Check if current cell is a target
        for (Cell* target : targets)
        {
            if (curr == target)
            {
                targetsFound[target] = true;
                // Return the first target found with minimum distance
                // Since we use a min-heap, this ensures shortest path
                return curr;
            }
        }

        for (Cell* neighbor : curr->adjacentCells)
        {
            if (!neighbor)
                continue;

            if (maze.CheckIfBlocked(curr, neighbor))
                continue;

            int newCost = costSoFar[curr] + 1;

            if (costSoFar.count(neighbor) == 0 || newCost < costSoFar[neighbor])
            {
                costSoFar[neighbor] = newCost;
                frontier.Insert(newCost, neighbor);
                cameFrom[neighbor] = curr;
            }
        }
    }

    // If no target is reachable, return start
    return start;
}

vector<Cell*> Dijkstra::FindPath(Maze& maze, Cell* start, const vector<Cell*>& targets)
{
    unordered_map<Cell*, Cell*> cameFrom;
    unordered_map<Cell*, int> costSoFar;
    vector<Cell*> path;

    Cell* pathEnd = Search(maze, start, targets, cameFrom, costSoFar);

    // Reconstruct path to the found target
    Cell* curr = pathEnd;
    Cell* prev = pathEnd;
    while (curr != start)
    {
        if (prev->GetDirection(curr) != curr->GetDirection(cameFrom[curr]))
            path.push_back(curr);

        prev = curr;
        curr = cameFrom[curr];
    }

    std::reverse(path.begin(), path.end());

    return path;
}