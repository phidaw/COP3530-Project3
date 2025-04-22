#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../Dijsktras/Dijkstra.h"
#include "DijkstraAgent.h"

void DijkstraAgent::UpdateVisuals()
{
    // todo -- update GUI here --
    // use this->currCell
}

std::future<vector<Cell*>> DijkstraAgent::CalculatePath(Mode mode, Maze& maze)
{
    if (mode == TraversalAgent::Mode::collecting)
    {
        // async policy ensures that this will run on a separate thread from main
        return std::async(std::launch::async,
            [this, &maze]()
            {
                const unordered_set<Collectable*> items = maze.graph.
                    regionMap.GetNearbyCollectables(currCell);

                // assign cells of all nearby items and maze exit as targets
                vector<Cell*> targets(items.size()+1);
                int i = 0;
                for (const auto* item : items)
                    targets[i++] = item->occupiedCell;
                targets[i] = maze.end;

                return Dijkstra::FindPath(maze, currCell, targets);
            });
    }

    // simple mode w/ no collectables
    return std::async(std::launch::async,
        [&maze]()
        {
            return Dijkstra::FindPath(maze, maze.start, {maze.end});
        });
}