#include <vector>
#include <queue>
#include <unordered_map>
#include "../../../Graph/Cell.h"
#include "../../../Maze/Maze.h"
#include "../../../Tools/RadixHeap/RadixHeapTriple.h"
#include "../../PathUtilities/PathUtilities.h"
#include "A_Star.h"

using std::vector;
using std::queue;
using std::unordered_map;

Cell* A_Star::Search(Maze& maze, Cell* start, Cell* end,
                    unordered_map<Cell*, Cell*>& cameFrom,
                    const int pathLimit)
{
    // manages priorities
    RadixHeapTriple frontier(maze.graph.GetCellNum());
    // manages G costs (dist from start to given cell)
    unordered_map<Cell*, int> costSoFar;
    // cameFrom: manages predecessors
    cameFrom[start] = start;
    costSoFar[start] = 0;
    frontier.Insert(0, 0, start);

    while (!frontier.Empty())
    {
        // get cell with lowest f cost
        Cell* curr = frontier.ExtractMin();

        // check if path is complete
        if (curr == end)
            return curr;

        // limit path length (due to arc of equal f-costs it will not be exact)
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
                // set G cost
                costSoFar[neighbor] = newCost;

                // calculate h cost
                int distToEnd = PathUtilities::ManhattanDist(neighbor->pos, end->pos);

                // set f cost = G cost + H cost
                int priority = newCost + distToEnd;

                // sort based on priority first, and use distToEnd as a tiebreaker
                frontier.Insert(priority, distToEnd, neighbor);

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
    int pathLimit = limitPath ? 10 : -1; // -1 == no limit
    unordered_map<Cell*, Cell*> cameFrom; // track predecessors
    vector<Cell*> path;

    // find path between start and end (returned path will not contain start)
    Cell* pathEnd = Search(maze, start, end, cameFrom, pathLimit);

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