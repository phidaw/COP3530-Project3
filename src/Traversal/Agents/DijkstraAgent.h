#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"

class DijkstraAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    void UpdateTimer() override;
public:
    DijkstraAgent(Cell* startCell) {
        currCell = startCell;
        name = "Dijksta";
    }
    std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
};
