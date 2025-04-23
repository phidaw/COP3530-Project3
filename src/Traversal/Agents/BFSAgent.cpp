#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../Algorithms/BFS/BFS.h"
#include "BFSAgent.h"

void BFSAgent::UpdateVisuals(const std::vector<Cell*>& path)
{
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.appendAgentPath(name, path); // Moved path appending here
    int tileSize = 32;
    if (toolbox.MazeSize > 29 && toolbox.MazeSize <= 59) tileSize = 16;
    else if (toolbox.MazeSize > 59 && toolbox.MazeSize <= 118) tileSize = 8;
    else if (toolbox.MazeSize > 118 && toolbox.MazeSize <= 317) tileSize = 3;

    if (currCell && currCell->pos->x < toolbox.MazeSize && currCell->pos->y < toolbox.MazeSize) {
        toolbox.mazeTilesTypes[currCell->pos->y][currCell->pos->x] = "head";
    }

    if (prevCell && prevCell->pos->x < toolbox.MazeSize && prevCell->pos->y < toolbox.MazeSize) {
        toolbox.mazeTilesTypes[prevCell->pos->y][prevCell->pos->x] = "path";
    }

    for (int y = 0; y < toolbox.MazeSize; ++y) {
        for (int x = 0; x < toolbox.MazeSize; ++x) {
            sf::Sprite sprite;
            const std::string& tileType = toolbox.mazeTilesTypes[y][x];

            if (tileType == "head") {
                if (tileSize == 32) sprite = toolbox.MazeSnakeHeadSprite;
                else if (tileSize == 16) sprite = toolbox.MazeSnakeHeadSprite16;
                else if (tileSize == 8) sprite = toolbox.MazeSnakeBodySprite8;
                else sprite = toolbox.MiniMazeSnakeSprite;
            } else if (tileType == "path") {
                if (tileSize == 32) sprite = toolbox.MazePathSprite;
                else if (tileSize == 16) sprite = toolbox.MazePathSprite16;
                else if (tileSize == 8) sprite = toolbox.MazePathSprite8;
                else sprite = toolbox.MiniMazePathSprite;
            } else {
                if (tileSize == 32) sprite = toolbox.MazeTileSprite;
                else if (tileSize == 16) sprite = toolbox.MazeTileSprite16;
                else if (tileSize == 8) sprite = toolbox.MazeTileSprite8;
                else sprite = toolbox.MiniMazeTileSprite;
            }

            sprite.setPosition(x * tileSize, y * tileSize);
            toolbox.mazeTiles[y][x] = sprite;
        }
    }
}

void BFSAgent::UpdateTimer()
{
    std::cout << name << "'s total time: " << totalTimeSpent << std::endl;
}

std::future<std::vector<Cell*>> BFSAgent::CalculatePath(Mode mode, Maze& maze)
{
    Toolbox& toolbox = Toolbox::getInstance();
    if (mode == TraversalAgent::Mode::collecting)
    {
        return std::async(std::launch::async,
                          [this, &maze]()
                          {
                              Cell* target = CalculateUtility(maze);
                              const auto start = std::chrono::high_resolution_clock::now();
                              auto path = BFS::FindPath(maze, currCell, target);
                              const auto end = std::chrono::high_resolution_clock::now();
                              const std::chrono::duration<double, std::milli> elapsed = end - start;
                              totalTimeSpent += elapsed.count();
                              return path;
                          });
    }

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
