#pragma once
#include "../../Graph/Cell.h"
#include "Array2D.h"

// forward declaration of incomplete type
class Cell;

struct CellArray2D : public Array2D<Cell>
{
    CellArray2D(unsigned int w, unsigned int h) :Array2D(w, h) {}
};