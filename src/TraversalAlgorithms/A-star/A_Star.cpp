#include <vector>
#include <queue>
#include <unordered_map>
#include "../../Graph/Graph.h"
#include "../../Graph/Cell.h"
#include "../../Graph/Edge.h"
#include "../../Graph/Position.h"
#include "../../Maze/Maze.h"
#include "../../Tools/Array2D/CellArray2D.h"
#include "A_Star.h"

using std::vector;
using std::queue;
using std::unordered_map;

int A_Star::ManhattanDistance(Position* p1, Position* p2)
{
    return std::abs(p1->x - p2->x) + std::abs(p1->y - p2->y);
}

// check if conjoining edge is within maze's walls
// if not, then there's a path between cells
bool A_Star::CheckIfBlocked(Cell* from, Cell* to, const Maze& maze)
{
    Edge* edge = Graph::GetSharedEdge(from, to);
    if (edge && maze.walls.count(edge) != 0)
        return true;

    return false;
}

void A_Star::Search(Maze& maze, Cell* start, Cell* end,
    CellArray2D& cameFrom,
    unordered_map<Cell*, int>& costSoFar)
{
    PriorityQueue<Cell*> frontier(start, 0);
    cameFrom.assign(start->pos->x, start->pos->y, start);
    costSoFar[start] = 0;

    while (!frontier.empty())
    {
        Cell* curr = frontier.top();
        if (curr == end) break; // path complete

        for (Cell* neighbor : curr->adjacentCells)
        {
            // check if edge between two cells is in maze
            if (CheckIfBlocked(curr, neighbor, maze))
                continue;

            // dist between two adjacent cells is 1
            int newCost = costSoFar[curr] + 1;

            // update dist between start and neighbor
            if (costSoFar.count(neighbor) == 0 || newCost < costSoFar[neighbor])
            {
                // set G cost (dist from start)
                costSoFar[neighbor] = newCost;
                // f cost = dist from start + dist to end
                int priority = newCost + ManhattanDistance(neighbor->pos, end->pos);
                frontier.insert(neighbor, priority);
                // set predecessor
                cameFrom.assign(neighbor->pos->x, neighbor->pos->y, curr);
            }
        }
    }
}

vector<Cell*> A_Star::FindPath(Maze& maze, Cell* start, Cell* end)
{
    CellArray2D cameFrom = maze.graph.cells; // can store this as an instance member, or elsewhere
    unordered_map<Cell*, int> costSoFar;
    vector<Cell*> path;

    // find path between start and end
    Search(maze, start, end, cameFrom, costSoFar);

    // since all cells in maze are connected, this should never occur:
    // if no path was found, return empty path
    // if (cameFrom.at(end) == nullptr)
    //     return path;

    // construct path from predecessor cells, end->start
    Cell* curr = end;
    while (curr != start)
    {
        path.push_back(curr);
        curr = cameFrom.at(curr);
    }
    // start->end
    std::reverse(path.begin(), path.end());

    return path;
}
