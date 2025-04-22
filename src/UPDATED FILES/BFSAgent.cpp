#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "../Algorithms/BFS/BFS.h"
#include "BFSAgent.h"
#include "../Toolbox.h"

void BFSAgent::UpdateVisuals()
{
    Toolbox& toolbox = Toolbox::getInstance();
    int tileSize = 32;
    if (toolbox.MazeSize > 29 && toolbox.MazeSize <= 59) tileSize = 16;
    else if (toolbox.MazeSize > 59 && toolbox.MazeSize <= 118) tileSize = 8;
    else if (toolbox.MazeSize > 118 && toolbox.MazeSize <= 317) tileSize = 3;

    headSprite->setPosition(currCell->pos->x * tileSize, currCell->pos->y * tileSize);
    toolbox.window.draw(*headSprite);

    if (prevCell) {
        pathSprites[0].setPosition(prevCell->pos->x * tileSize, prevCell->pos->y * tileSize);
        toolbox.window.draw(pathSprites[0]);
    }
}

void BFSAgent::UpdateTimer()
{
    std::cout << name << "'s total time: " << totalTimeSpent << std::endl;
}

std::future<std::vector<Cell*>> BFSAgent::CalculatePath(Mode mode, Maze& maze)
{
    return std::async(std::launch::async, [this, mode, &maze]()
    {
        Cell* target = mode == Mode::traversal ? maze.end : CalculateUtility(maze);
        totalTimeSpent += (rand() % 10) / 10.0;

        return BFS::FindPath(maze, currCell, target);
    });
}