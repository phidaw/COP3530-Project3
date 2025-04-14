#pragma once
#include <vector>
#include "Position.h"
#include "Edge.h"
#include "Graph.h"
using std::vector;

// https://stackoverflow.com/questions/8526819/c-header-files-including-each-other-mutually
class Graph;

class Cell
{
public:
    enum OrdinalDir { NW, NE, SW, SE };
    enum CardinalDir { North, East, South, West, center };

    // for traversal algorithms
    // bool isFull
    // obj ObjectInCell

    // for prim's algorithm
    bool discovered = false;

    const static int numDir = 4;

    Position* pos;
    Position* vertices[numDir]{};
    Edge* edges[numDir]{};
    Cell* adjacentCells[numDir]{};

    Cell() {}
    Cell(Graph* graph, Position* pos);

    void AssignAdjacentCells(Graph* graph);
    void AssignEdge(Edge* edge);
    void AssignEdges(Edge* horEdge, Edge* verEdge);

    CardinalDir GetDirection(Cell* to) const;
    Edge* GetSharedEdge(Cell* nCell) const;
};