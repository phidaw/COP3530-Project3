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
#include <SFML/Graphics.hpp> // Add SFML for sprite drawing

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

    // Add sprite-related members
    sf::Sprite* headSprite = nullptr; // Agent's head sprite
    std::vector<sf::Sprite> pathSprites; // Sprites for the agent's path
    Cell* prevCell = nullptr; // To track previous cell for path drawing

protected:
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
        prevCell = currCell; // Store the previous cell before moving
        currCell = cell;

        std::cout << "moved to: " << currCell->pos << std::endl;

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

inline Collectable* TraversalAgent::GetMaxItemUtility(double& maxItemUtility, const Maze& maze)
{
    Collectable* maxItem = nullptr;
    maxItemUtility = 0;

    for (Collectable* item : maze.graph.collectables)
    {
        if (itemsCollected.find(item) != itemsCollected.end())
            continue;

        double distToItem = PathUtilities::ManhattanDist(currCell->pos, item->pos);
        if (distToItem == 0) continue;

        double distToEnd = PathUtilities::ManhattanDist(item->pos, maze.end->pos);
        double utility = Logit(distToItem, -2, 0.5) + Logit(distToEnd, -2, 0.5);

        if (utility > maxItemUtility)
        {
            maxItemUtility = utility;
            maxItem = item;
        }
    }

    return maxItem;
}

inline Cell* TraversalAgent::CalculateUtility(Maze& maze)
{
    double maxItemUtility;
    Collectable* maxItem = GetMaxItemUtility(maxItemUtility, maze);

    if (!maxItem)
        return maze.end;

    double distToEnd = PathUtilities::ManhattanDist(currCell->pos, maze.end->pos);
    double utilityEnd = Logit(distToEnd, -2, 0.5);

    return utilityEnd > maxItemUtility ? maze.end : maxItem->cell;
}