#include <vector>
#include "Position.h"
#include "Edge.h"
#include "Graph.h"
#include "Cell.h"
using std::vector;

Cell::Cell(Graph* graph, Position* p)
{
    // the pos of the cell is its pivot vertex
    // where the pivot is its top-left vertex
    this->pos = p;

    int x = pos->x;
    int y = pos->y;

    auto& graphNodes = graph->vertices;

    // set vertices
    vertices[OrdinalDir::NW] = pos;
    vertices[OrdinalDir::NE] = graphNodes.at(x + 1, y);
    vertices[OrdinalDir::SW] = graphNodes.at(x, y + 1);
    vertices[OrdinalDir::SE] = graphNodes.at(x + 1, y + 1);
}

void Cell::AssignAdjacentCells(Graph* graph)
{
    int x = pos->x;
    int y = pos->y;

    auto& graphCells = graph->cells;

    // set adjacent cells
    adjacentCells[CardinalDir::North] = graphCells.at(x, y - 1);
    adjacentCells[CardinalDir::East] = graphCells.at(x + 1, y);
    adjacentCells[CardinalDir::South] = graphCells.at(x, y + 1);
    adjacentCells[CardinalDir::West] = graphCells.at(x - 1, y);
}

void Cell::AssignEdge(Edge* edge)
{
    if (edge->GetDirection() == Edge::Direction::Horizontal)
        edges[CardinalDir::South] = edge;
    else
        edges[CardinalDir::East] = edge;
}
void Cell::AssignEdges(Edge* horEdge, Edge* verEdge)
{
    edges[CardinalDir::North] = horEdge;
    edges[CardinalDir::West] = verEdge;

    Cell* top = adjacentCells[CardinalDir::North];
    if (top)
        top->edges[CardinalDir::South] = horEdge;

    Cell* left = adjacentCells[CardinalDir::West];
    if (left)
        left->edges[CardinalDir::East] = verEdge;
}

Cell::CardinalDir Cell::GetDirection(Cell* to) const
{
    if (!to)
        return center;

    for (int i = 0; i < Cell::numDir; i++)
    {
        if (adjacentCells[i] == to)
            return static_cast<CardinalDir>(i);
    }

    return center;
}

Edge* Cell::GetSharedEdge(Cell* nCell) const
{
    auto direction = GetDirection(nCell);

    // if the cells are adjacent...
    if (direction != CardinalDir::center)
        return edges[direction];

    return nullptr;
}
