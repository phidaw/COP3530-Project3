#include <vector>
#include "Position.h"
#include "Edge.h"
#include "Cell.h"
#include "../Tools/Array2D/CellArray2D.h"
#include "../Tools/Array2D/Array2D.h"
#include "../Tools/CompassDir/CompassDir.h"

using std::vector;

Cell::Cell(Array2D<Position>& vertices, Position* p)
{
    // the pos of the cell is its pivot vertex
    // where the pivot is its top-left vertex
    this->pos = p;

    int x = pos->x;
    int y = pos->y;

    // set vertices
    this->vertices[Ordinal::NW] = pos;
    this->vertices[Ordinal::NE] = vertices.at(x + 1, y);
    this->vertices[Ordinal::SW] = vertices.at(x, y + 1);
    this->vertices[Ordinal::SE] = vertices.at(x + 1, y + 1);
}

void Cell::AssignAdjacentCells(CellArray2D& cells)
{
    int x = pos->x;
    int y = pos->y;

    // set adjacent cells
    adjacentCells[Cardinal::North] = cells.at(x, y - 1);
    adjacentCells[Cardinal::East] = cells.at(x + 1, y);
    adjacentCells[Cardinal::South] = cells.at(x, y + 1);
    adjacentCells[Cardinal::West] = cells.at(x - 1, y);
}

void Cell::AssignTopEdge(Edge* edge)
{
    edges[Cardinal::North] = edge;

    Cell* top = adjacentCells[Cardinal::North];
    if (top)
        top->edges[Cardinal::South] = edge;
}
void Cell::AssignLeftEdge(Edge* edge)
{
    edges[Cardinal::West] = edge;

    Cell* left = adjacentCells[Cardinal::West];
    if (left)
        left->edges[Cardinal::East] = edge;
}
void Cell::AssignBotEdge(Edge* edge)
{
    edges[Cardinal::South] = edge;
}
void Cell::AssignRightEdge(Edge* edge)
{
    edges[Cardinal::East] = edge;
}

Cardinal Cell::GetDirection(Cell* to) const
{
    if (!to)
        return Cardinal::center;

    for (int i = 0; i < Cell::numDir; i++)
    {
        if (adjacentCells[i] == to)
            return static_cast<Cardinal>(i);
    }

    // 'to' is not adjacent to *this
    return Cardinal::center;
}

Edge* Cell::GetSharedEdge(Cell* nCell) const
{
    auto direction = GetDirection(nCell);

    // if the cells are adjacent...
    if (direction != Cardinal::center)
        return edges[direction];

    return nullptr;
}