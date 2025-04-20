#include <iostream>
#include <chrono>
#include <future>
#include <unordered_set>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../PathUtilities/PathUtilities.h"
#include "../../Graph/Collectable.h"
#include "AStarAgent.h"

void AStarAgent::UpdateVisuals()
{
    // todo -- update GUI here --
    // use this->currCell
}

vector<Cell*> AStarAgent::ComplexTraversal(Maze& maze)
{
    // todo phi: swap duration with (C x sfml frame length)
    // calculate utility every 'n' frames
    // note: not needed, unless we're doing multi-threading for SFML as well
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // get item with max utility (shortest dist to agent)
    double maxItemUtility = 0;
    const Collectable* maxItem = GetMaxItemUtility(maxItemUtility, maze);

    // calculate utility for exiting maze
    Cell* target = maze.end;
    int distToExit = PathUtilities::ManhattanDist(currCell->pos, maze.end->pos);
    double exitUtility = Logit(distToExit, 5, 10);

    // todo phi: add distance traveled variable and item quota (if any)
    // compare utilities, erring in favor of collecting the item
    if (maxItem && exitUtility - maxItemUtility <= 0.0)
    {
        // item utility overpowers exit utility, agent will go to item
        target = maxItem->occupiedCell;
    }

    // todo phi: limit path
    // limiting path length since current objective can change frequently
    auto path = A_Star::FindPath(maze, maze.start, target);

    return path;
}

std::future<vector<Cell*>> AStarAgent::CalculatePath(Mode mode, Maze& maze)
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
        [&maze]()
        {
            return A_Star::FindPath(maze, maze.start, maze.end);
        });
}

void AStarAgent::Move(vector<Cell*>& path, const Cell* exit)
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