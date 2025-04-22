#include <iostream>
#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/Dijkstra/Dijkstra.h"
#include "../PathUtilities/PathUtilities.h"
#include "../../Graph/Collectable.h"
#include "DijkstraAgent.h"

void DijkstraAgent::UpdateVisuals()
{
    // todo -- update GUI here --
    // use this->currCell
}

std::vector<Cell*> DijkstraAgent::ComplexTraversal(Maze& maze)
{
    // get item with max utility (shortest dist to agent)
    double maxItemUtility = 0;
    const Collectable* maxItem = GetMaxItemUtility(maxItemUtility, maze);

    // set targets: always include maze exit, add item if available
    std::vector<Cell*> targets = {maze.end};
    if (maxItem)
    {
        targets.push_back(maxItem->occupiedCell);
    }

    // find path to closest target
    auto path = Dijkstra::FindPath(maze, currCell, targets);

    return path;
}

std::future<vector<Cell*>> DijkstraAgent::CalculatePath(Mode mode, Maze& maze)
{
if (mode == TraversalAgent::Mode::collecting)
{
// async policy ensures that this will run on a separate thread from main
return std::async(std::launch::async,
[this, &maze]()
{
return ComplexTraversal(maze);
});
}

// simple mode w/ no collectables, so no need to limit path
return std::async(std::launch::async,
[&maze, this]()
{
return Dijkstra::FindPath(maze, currCell, {maze.end});
});
}

void DijkstraAgent::Move(vector<Cell*>& path, const Cell* exit)
{
    std::cout << "------------ " << name << " started a new path ------------" << std::endl;
    std::cout << "start: " << currCell->pos << std::endl;

    // if current/starting cell has an item, collect it
    if (currCell->objectInCell)
    {
        if (itemsCollected.emplace(currCell->objectInCell).second)
            std::cout << name << " collected an item at: " << currCell->pos << std::endl;
    }

    for (Cell* cell : path)
    {
        // move to current cell in path
        totalDistTraveled++;
        currCell = cell;

        std::cout << "moved to: " << currCell->pos << std::endl;

        // collect item in current cell, if any
        if (cell->objectInCell)
        {
            if (itemsCollected.emplace(currCell->objectInCell).second)
                std::cout << name << " collected an item at: " << currCell->pos << std::endl;
        }

        UpdateVisuals();
    }

    if (currCell == exit)
        exitedMaze = true;
}