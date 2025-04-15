#include <vector>
#include <queue>
#include <unordered_map>
#include "../../../Graph/Cell.h"
#include "../../../Maze/Maze.h"
#include "../../../Tools/MinHeap/MinHeap.h"
#include "A_Star.h"

#include "../../PathUtilities/PathUtilities.h"

using std::vector;
using std::queue;
using std::unordered_map;

Cell* A_Star::Search(Maze& maze, Cell* start, Cell* end,
                    unordered_map<Cell*, Cell*>& cameFrom,
                    unordered_map<Cell*, int>& costSoFar,
                    const int pathLimit)
{
    MinHeap<Cell*> frontier(start, 0); // open, closed, and priority
    costSoFar[start] = 0;
    cameFrom[start] = start;

    while (!frontier.empty())
    {
        // get cell with lowest f cost
        Cell* curr = frontier.extract();

        // path complete
        if (curr == end)
            return curr;

        // limit path length (due to randomness of maze, it will not be exact)
        if (pathLimit > 0 && costSoFar[curr] >= pathLimit)
            return curr;

        for (Cell* neighbor : curr->adjacentCells)
        {
            if (!neighbor)
                continue;

            // check if edge between two cells is in maze
            if (maze.CheckIfBlocked(curr, neighbor))
                continue;

            // dist between two adjacent cells is 1
            int newCost = costSoFar[curr] + 1;

            // update dist between start and neighbor
            if (costSoFar.count(neighbor) == 0 || newCost < costSoFar[neighbor])
            {
                // set G cost (dist from start)
                costSoFar[neighbor] = newCost;

                // f cost = G cost + H cost (dist to end)
                int priority = newCost + PathUtilities::ManhattanDist(neighbor->pos, end->pos);
                frontier.insert(neighbor, priority);

                // set neighbor's predecessor
                cameFrom[neighbor] = curr;
            }
        }
    }

    // no path found, end of path is start
    return start;
}

vector<Cell*> A_Star::FindPath(Maze& maze, Cell* start, Cell* end, bool limitPath)
{
    int pathLimit = limitPath ? 5 : -1; // -1 == no limit
    unordered_map<Cell*, Cell*> cameFrom; // track predecessors
    unordered_map<Cell*, int> costSoFar; // track priorities
    vector<Cell*> path;

    // find path between start and end (returned path will not contain start)
    Cell* pathEnd = Search(maze, start, end, cameFrom, costSoFar, pathLimit);

    // reconstruct path
    Cell* curr = pathEnd;
    Cell* prev = pathEnd;
    while (curr != start)
    {
        // add curr if cameFrom[curr] -> curr -> prev is not a straight path
        if (prev->GetDirection(curr) != curr->GetDirection(cameFrom[curr]))
            path.push_back(curr);

        prev = curr;
        curr = cameFrom[curr];
    }

    // order from start->end
    std::reverse(path.begin(), path.end());

    return path;
}