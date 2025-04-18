#pragma once
#include <vector>
#include "Collectable.h"
#include "Position.h"
#include "Edge.h"
#include "../Tools/Array2D/CellArray2D.h"
#include "../Tools/CompassDir/CompassDir.h"

using std::vector;

// forward declaration of incomplete type
struct CellArray2D;
struct Collectable;

class Cell
{
public:
    // for prim's algorithm
    bool discovered = false;

    // for traversal agents
    Collectable* objectInCell = nullptr;

    const static int numDir = 4;

    Position* pos;
    Position* vertices[numDir]{};
    Edge* edges[numDir]{};
    Cell* adjacentCells[numDir]{};

    Cell() {}
    Cell(Array2D<Position>& vertices, Position* pos);

    void AssignAdjacentCells(CellArray2D& cells);

    void AssignTopEdge(Edge* edge);
    void AssignLeftEdge(Edge* edge);
    void AssignBotEdge(Edge* edge);
    void AssignRightEdge(Edge* edge);

    Cardinal GetDirection(Cell* to) const;
    Edge* GetSharedEdge(Cell* nCell) const;
};