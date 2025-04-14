#include "../../Graph/Cell.h"
#include "CellArray2D.h"

Cell* CellArray2D::atCell(Cell* cell)
{
    int x = cell->pos->x;
    int y = cell->pos->y;
    return CheckIfInRange(x, y) ? arr[y*width + x] : nullptr;
}

const Cell* CellArray2D::atCell(Cell* cell) const
{
    int x = cell->pos->x;
    int y = cell->pos->y;
    return CheckIfInRange(x, y) ? arr[y*width + x] : nullptr;
}