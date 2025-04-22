#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"

class AStarAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    void UpdateTimer() override;
public:
    AStarAgent(Cell* startCell) {
        currCell = startCell;
        name = "A*";
    }
    std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
};
