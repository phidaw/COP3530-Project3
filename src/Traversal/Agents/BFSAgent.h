#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"

class BFSAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    void UpdateTimer() override;
public:
    BFSAgent(Cell* startCell) {
        currCell = startCell;
        name = "BFS";
    }
    std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
};