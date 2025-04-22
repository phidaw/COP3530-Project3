#pragma once
#include <string>
#include <vector>
#include <future>
#include "../../Maze/Maze.h"
#include "TraversalAgent.h"
#include "../Algorithms/Dijkstra/Dijkstra.h"

class DijkstraAgent : public TraversalAgent
{
    void UpdateVisuals() override;
    std::vector<Cell*> ComplexTraversal(Maze& maze) override;
public:
    DijkstraAgent(Cell* startCell) {
        currCell = startCell;
        name = "Dijkstra";
    }
    std::future<vector<Cell*>> CalculatePath(Mode mode, Maze& maze) override;
    void Move(vector<Cell*>& path, const Cell* exit) override;
};