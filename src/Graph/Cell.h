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
    enum CardinalDir { North, East, South, West };

    // for traversal algorithms
    // bool isFull
    // obj ObjectInCell

    // for prim's algorithm
    bool discovered = false;

    Position* pos;
    Position* vertices[4]{};
    Edge* edges[4]{};
    Cell* adjacentCells[4]{};

    Cell() {}
    Cell(Graph* graph, Position* pos);

    void AssignAdjacentCells(Graph* graph);
    void AssignEdge(Edge* edge);
    void AssignEdges(Edge* horEdge, Edge* verEdge);
};