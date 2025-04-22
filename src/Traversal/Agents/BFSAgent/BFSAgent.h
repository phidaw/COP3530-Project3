#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"
#include "../Algorithms/BFS/BFS.h"

class BFSAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    std::vector<Cell*> ComplexTraversal(Maze& maze) override;
public:
    BFSAgent(Cell* startCell) {
        currCell = startCell;
        name = "BFS";
    }
    std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
    void Move(vector<Cell*>& path, const Cell* exit) override;
};