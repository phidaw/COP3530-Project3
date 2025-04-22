#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "AStarAgent.h"

void AStarAgent::UpdateVisuals()
{
    // todo -- update GUI here --
    // use this->currCell
}

void AStarAgent::UpdateTimer()
{
    std::cout << name << "'s total time: " << totalTimeSpent << std::endl;
}

std::future<vector<Cell*>> AStarAgent::CalculatePath(Mode mode, Maze& maze)
{
    if (mode == TraversalAgent::Mode::collecting)
    {
        // async policy ensures that this will run on a separate thread from main
        return std::async(std::launch::async,
            [this, &maze]()
            {
                // todo phi: limit path
                // limiting path length since current objective can change frequently

                Cell* target = CalculateUtility(maze);

                // timing execution time of A*
                const auto start = std::chrono::high_resolution_clock::now();

                auto path = A_Star::FindPath(maze, currCell, target);

                const auto end = std::chrono::high_resolution_clock::now();
                const std::chrono::duration<double, std::milli> elapsed = end - start;

                totalTimeSpent += elapsed.count();

                return path;
            });
    }

    // simple mode w/ no collectables, so no need to limit path
    return std::async(std::launch::async,
        [this, &maze]()
        {
            const auto start = std::chrono::high_resolution_clock::now();

            auto path = A_Star::FindPath(maze, maze.start, maze.end);

            const auto end = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> elapsed = end - start;

            totalTimeSpent += elapsed.count();

            return path;
        });
}
