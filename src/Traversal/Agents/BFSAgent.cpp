#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../Algorithms/BFS/BFS.h"
#include "BFSAgent.h"

void BFSAgent::UpdateVisuals()
{
    // todo -- update GUI here --
    // use this->currCell
}

void BFSAgent::UpdateTimer()
{
    std::cout << name << "'s total time: " << totalTimeSpent << std::endl;
}

std::future<vector<Cell*>> BFSAgent::CalculatePath(Mode mode, Maze& maze)
{
    if (mode == TraversalAgent::Mode::collecting)
    {
        // async policy ensures that this will run on a separate thread from main
        return std::async(std::launch::async,
            [this, &maze]()
            {
                Cell* target = CalculateUtility(maze);

                // timing execution time of BFS
                const auto start = std::chrono::high_resolution_clock::now();

                auto path = BFS::FindPath(maze, currCell, target);

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

            auto path = BFS::FindPath(maze, maze.start, maze.end);

            const auto end = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> elapsed = end - start;

            totalTimeSpent += elapsed.count();

            return path;
        });
}
