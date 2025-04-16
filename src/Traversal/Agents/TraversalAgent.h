#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <future>
#include "../../Graph/RegionMap.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../../Graph/Collectable.h"
#include "../PathUtilities/PathUtilities.h"

#define LOG_10_e 0.43429448

class TraversalAgent
{
public:
    enum Mode { traversal, collecting };
    virtual ~TraversalAgent() {}

    virtual std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) = 0;
    virtual void Move(vector<Cell*>& path, const Cell* exit) = 0;

    virtual void CollectItem(Collectable* item) {
        itemsCollected.emplace(item);
    }
    static double Logit(double x, double shift= 0, double stretch = 1) {
        if (x == 1) return x;
        x = 1/x;
        return (log10(x/(1.0-x)) / LOG_10_e + shift) / stretch;
    }

    std::string GetName() const { return name; }
    bool CheckIfExitedMaze() const { return exitedMaze; }
    int GetTotalDistanceTraveled() const { return totalDistTraveled; }
    int GetTotalItemsCollected() const { return itemsCollected.size(); }

protected:
    // const static int DEFAULT_VISION_RADIUS = 5;
    std::string name;
    Cell* currCell = nullptr;
    bool exitedMaze = false;
    int totalDistTraveled = 0;
    unordered_set<Collectable*> itemsCollected;

    virtual void UpdateVisuals() = 0;
    virtual std::vector<Cell*> ComplexTraversal(Maze& maze) = 0;
    Collectable* GetMaxItemUtility(double& maxItemUtility, const Maze& maze)
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
};