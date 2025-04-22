#include <queue>
#include <unordered_map>
#include "../../../Graph/Cell.h"
#include "../../../Maze/Maze.h"
#include "../../PathUtilities/PathUtilities.h"
#include "BFS.h"

using std::queue;
using std::unordered_map;

Cell* BFS::Search(Maze& maze, Cell* start, Cell* end,
                  unordered_map<Cell*, Cell*>& cameFrom)
{
    queue<Cell*> frontier;
    frontier.push(start);
    cameFrom[start] = start;

    while (!frontier.empty())
    {
        Cell* curr = frontier.front();
        frontier.pop();

        if (curr == end)
            return curr;

        for (Cell* neighbor : curr->adjacentCells)
        {
            if (!neighbor)
                continue;

            if (maze.CheckIfBlocked(curr, neighbor))
                continue;

            if (cameFrom.count(neighbor) == 0)
            {
                frontier.push(neighbor);
                cameFrom[neighbor] = curr;
            }
        }
    }

    return start;
}

vector<Cell*> BFS::FindPath(Maze& maze, Cell* start, Cell* end)
{
    unordered_map<Cell*, Cell*> cameFrom;
    vector<Cell*> path;

    Cell* pathEnd = Search(maze, start, end, cameFrom);

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
