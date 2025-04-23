#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../Algorithms/Dijsktras/Dijkstra.h"
#include "DijkstraAgent.h"

void DijkstraAgent::UpdateVisuals()
{
    Toolbox& toolbox = Toolbox::getInstance();
    int tileSize = 32;
    if (toolbox.MazeSize > 29 && toolbox.MazeSize <= 59) tileSize = 16;
    else if (toolbox.MazeSize > 59 && toolbox.MazeSize <= 118) tileSize = 8;
    else if (toolbox.MazeSize > 118 && toolbox.MazeSize <= 317) tileSize = 3;

    // Update mazeTileTypes for current cell (agent's head)
    if (currCell && currCell->pos->x < toolbox.MazeSize && currCell->pos->y < toolbox.MazeSize) {
        toolbox.mazeTilesTypes[currCell->pos->y][currCell->pos->x] = "head";
    }

    // Update mazeTileTypes for previous cell (path)
    if (prevCell && prevCell->pos->x < toolbox.MazeSize && prevCell->pos->y < toolbox.MazeSize) {
        toolbox.mazeTilesTypes[prevCell->pos->y][prevCell->pos->x] = "path";
    }

void DijkstraAgent::UpdateTimer()
{
    std::cout << name << "'s total time: " << totalTimeSpent << std::endl;
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
                for (auto* item : items)
                {
                    // only include non-collected items
                    if (itemsCollected.find(item) == itemsCollected.end())
                        targets[i++] = item->occupiedCell;
                }
                targets[i] = maze.end;

                // timing execution time of Dijksta's
                const auto start = std::chrono::high_resolution_clock::now();

                auto path = Dijkstra::FindPath(maze, currCell, targets);

                const auto end = std::chrono::high_resolution_clock::now();
                const std::chrono::duration<double, std::milli> elapsed = end - start;

                totalTimeSpent += elapsed.count();

                return path;
            });
    }

    // simple mode w/ no collectables
    return std::async(std::launch::async,
        [this, &maze]()
        {
            const auto start = std::chrono::high_resolution_clock::now();

            auto path = Dijkstra::FindPath(maze, maze.start, {maze.end});

            const auto end = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> elapsed = end - start;

            totalTimeSpent += elapsed.count();

            return path;
        });
}
