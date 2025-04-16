#pragma once
#include "Cell.h"

// forward declaration of incomplete type
class Cell;

struct Collectable
{
    Cell* occupiedCell;
    Collectable(Cell* cell = nullptr) : occupiedCell(cell) {}
};