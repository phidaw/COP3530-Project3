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

    virtual std::future<std::vector<Cell*>> CalculatePath(Mode mode, Maze& maze) = 0;
    void Move(std::vector<Cell*>& path, const Cell* exit);

    void ResetTimeCounter() { totalTimeSpent = 0.0; }
    std::string GetName() const { return name; }
    bool CheckIfExitedMaze() const { return exitedMaze; }
    int GetTotalDistanceTraveled() const { return totalDistTraveled; }
    double GetTotalTimeSpent() const { return totalTimeSpent; }
    int GetTotalItemsCollected() const { return itemsCollected.size(); }

protected:
    std::string name;
    Cell* currCell = nullptr;
    bool exitedMaze = false;
    int totalDistTraveled = 0;
    double totalTimeSpent = 0.0;
    std::unordered_set<Collectable*> itemsCollected;

    virtual void UpdateVisuals(const std::vector<Cell*>& path) = 0;
    virtual void UpdateTimer() = 0;
    Collectable* GetMaxItemUtility(double& maxItemUtility, const Maze& maze);
    Cell* CalculateUtility(Maze& maze);

    static double Logit(double x, double shift = 0, double stretch = 1) {
        if (x == 1) return x;
        x = 1/x;
        return (std::log(x/(1.0-x)) / LOG_10_e + shift) / stretch;
    }
};

inline Collectable* TraversalAgent::GetMaxItemUtility(double& maxItemUtility, const Maze& maze)
{
    const RegionMap& regionMap = maze.graph.regionMap;
    const std::unordered_set<Collectable*> items = regionMap.GetNearbyCollectables(currCell);

    Collectable* maxItem = nullptr;
    for (Collectable* item : items)
    {
        const Cell* itemCell = item->occupiedCell;
        if (itemsCollected.find(item) != itemsCollected.end())
            continue;

        double utility = PathUtilities::ManhattanDist(currCell->pos, itemCell->pos);
        utility = utility == 0 ? 0 : 1.0/utility;
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
    double maxItemUtility = 0;
    const Collectable* maxItem = GetMaxItemUtility(maxItemUtility, maze);
    Cell* target = maze.end;
    int distToExit = PathUtilities::ManhattanDist(currCell->pos, maze.end->pos);
    double exitUtility = Logit(distToExit, 5, 10);

    if (maxItem && exitUtility - maxItemUtility <= 0.0)
    {
        target = maxItem->occupiedCell;
    }
    return target;
}

inline void TraversalAgent::Move(std::vector<Cell*>& path, const Cell* exit)
{
    std::cout << "------------ " << name << " started a new path ------------" << std::endl;
    std::cout << "start: " << currCell->pos << std::endl;

    if (currCell->objectInCell)
    {
        if (itemsCollected.emplace(currCell->objectInCell).second)
            std::cout << name << " collected an item at: " << currCell->pos << std::endl;
    }

    for (Cell* cell : path)
    {
        totalDistTraveled++;
        currCell = cell;

        std::cout << "moved to: " << currCell->pos << std::endl;

        if (cell->objectInCell)
        {
            if (itemsCollected.emplace(currCell->objectInCell).second)
                std::cout << name << " collected an item at: " << currCell->pos << std::endl;
        }
    }

    UpdateVisuals(path);

    if (currCell == exit)
    {
        exitedMaze = true;
        UpdateTimer();
    }
}
