#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "AStarAgent.h"

void AStarAgent::UpdateVisuals()
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
