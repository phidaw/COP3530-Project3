#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"
#include "../Toolbox.h" // Include Toolbox for sprite access

class AStarAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    void UpdateTimer() override;
public:
    AStarAgent(Cell* startCell) {
        currCell = startCell;
        name = "A*";
        // Initialize sprites using Toolbox
        Toolbox& toolbox = Toolbox::getInstance();
        headSprite = &toolbox.MazeSnakeHeadSprite;
        pathSprites.resize(1); // Resize for initial path segment
        pathSprites[0] = toolbox.MazeSnakeBodySprite;
    }
    std::future<std::vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
};