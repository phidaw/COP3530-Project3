#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"
#include "../Toolbox.h"

class DijkstraAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    void UpdateTimer() override;
public:
    DijkstraAgent(Cell* startCell) {
        currCell = startCell;
        name = "Dijkstra"; // Corrected typo from "Dijksta"
        Toolbox& toolbox = Toolbox::getInstance();
        headSprite = &toolbox.MazeSnakeHeadSprite;
        pathSprites.resize(1);
        pathSprites[0] = toolbox.MazeSnakeBodySprite;
    }
    std::future<std::vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
};