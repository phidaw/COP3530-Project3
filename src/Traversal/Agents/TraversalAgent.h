#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <future>
#include "../../Maze/Maze.h"
#include "../../Graph/RegionMap.h"
#include "../../Graph/Collectable.h"
#include "../PathUtilities/PathUtilities.h"

#define LOG_10_e 0.43429448

class TraversalAgent
{
public:
    enum Mode { traversal, collecting };
    virtual ~TraversalAgent() {}

    virtual std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) = 0;
    void Move(vector<Cell*>& path, const Cell* exit);

    void ResetTimeCounter() { totalTimeSpent = 0.0; }
    std::string GetName() const { return name; }
    bool CheckIfExitedMaze() const { return exitedMaze; }
    int GetTotalDistanceTraveled() const { return totalDistTraveled; }
    double GetTotalTimeSpent() const { return totalTimeSpent; }
    int GetTotalItemsCollected() const { return itemsCollected.size(); }

protected:
    // const static int DEFAULT_VISION_RADIUS = 5;
    std::string name;
    Cell* currCell = nullptr;
    bool exitedMaze = false;
    int totalDistTraveled = 0;
    double totalTimeSpent = 0.0;
    std::unordered_set<Collectable*> itemsCollected;

    virtual void UpdateVisuals() = 0;
    virtual void UpdateTimer() = 0;
    Collectable* GetMaxItemUtility(double& maxItemUtility, const Maze& maze);
    Cell* CalculateUtility(Maze& maze);

    static double Logit(double x, double shift = 0, double stretch = 1) {
        if (x == 1) return x;
        x = 1/x;
        return (log10(x/(1.0-x)) / LOG_10_e + shift) / stretch;
    }
};

inline Collectable* TraversalAgent::GetMaxItemUtility(double& maxItemUtility, const Maze& maze)
{
    const RegionMap& regionMap = maze.graph.regionMap;

    // if this causes a data race, execute in main thread, prior to returning lambda in Execute()
    // gathers all items within region stored in graph
    const unordered_set<Collectable*> items = regionMap.GetNearbyCollectables(currCell);

    // get item with max utility (shortest dist to agent)
    Collectable* maxItem = nullptr;
    for (Collectable* item : items)
    {
        const Cell* itemCell = item->occupiedCell;

        // calculate utility only for non-collected items
        if (itemsCollected.find(item) != itemsCollected.end())
            continue;

        double utility = PathUtilities::ManhattanDist(currCell->pos, itemCell->pos);
        utility = utility == 0 ? 0 : 1.0/utility; // utility of time
        if (maxItemUtility < utility)
        {
            maxItemUtility = utility;
            maxItem = item;
        }
    }

    return maxItem;
}

inline Cell* TraversalAgent::CalculateUtility(Maze& maze)
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

    return target;
}

inline void TraversalAgent::Move(vector<Cell*>& path, const Cell* exit)
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
    {
        exitedMaze = true;
        UpdateTimer();
    }
}