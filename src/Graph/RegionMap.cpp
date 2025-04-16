#include "RegionMap.h"
#include <unordered_set>
#include <unordered_map>
#include "Cell.h"
#include "Collectable.h"
#include "../Tools/Array2D/CellArray2D.h"
#include "../Tools/Array2D/Array2D.h"
#include "../Tools/CompassDir/CompassDir.h"
#include "../Tools/Random/Random.h"

RegionMap::~RegionMap()
{
    for (auto& kvp : collectables)
    {
        for (auto* item : kvp.second)
            delete item;
    }
}

// void RegionMap::SetRegions(Array2D<Position>& vertices)
// {
//     // note: assuming that graph is a square matrix
//     // delineate regions by top-left and bottom-right corners
//     const int mid = width/2.0f + 0.5f;
//     Position* a0 = vertices.at(0, 0);
//     Position* midPos = vertices.at(mid, mid);
//     Position* b0 = vertices.at(mid, 0);
//     Position* b1 = vertices.at(width, mid);
//     Position* c0 = vertices.at(0, mid);
//     Position* c1 = vertices.at(mid, width);
//     Position* d1 = vertices.at(width, width);
//
//     regions[Ordinal::NW] = std::make_pair(a0, midPos);
//     regions[Ordinal::NE] = std::make_pair(b0, b1);
//     regions[Ordinal::SW] = std::make_pair(c0, c1);
//     regions[Ordinal::SE] = std::make_pair(midPos, d1);
// }

Ordinal RegionMap::GetRegion(const Cell* const cell) const
{
    /** spawn collectables per region
         * if odd num of cellsPerRow, regions are overlapping
         * NW gets right intersection
         * NE gets bottom intersection
         * SW gets top intersection
         * SE gets left intersection, and center cell
         */

    int x = cell->pos->x;
    int y = cell->pos->y;
    int mid = width/2;

    Ordinal direction = Ordinal::SE;
    if (width % 2 != 0)
    {
        if (x <= mid && y < mid)
            direction = Ordinal::NW;
        else if (x > mid && y <= mid)
            direction = Ordinal::NE;
        else if (x < mid && y >= mid)
            direction = Ordinal::SW;
        else // includes center-most cell
            direction = Ordinal::SE;
    }
    else
    {
        if (x < mid)
        {
            if (y < mid)
                direction = Ordinal::NW;
            else
                direction = Ordinal::SW;
        }
        else
        {
            if (y < mid)
                direction = Ordinal::NE;
            else
                direction = Ordinal::SE;
        }
    }

    return direction;
}

void RegionMap::AssignItem(Cell* cell)
{
    auto* item = new Collectable(cell);
    item->occupiedCell = cell;
    cell->objectInCell = item;
    collectables[GetRegion(cell)].emplace(item);
}

void RegionMap::DistributeItems(CellArray2D& cells)
{
    const int itemNum = cells.Width() / 2;
    rand.ChangeBounds(0, cells.Width()-1);
    for (int i = 0; i < itemNum; i++)
    {
        // assign random cell w/ collectable, if not already assigned
        Cell* cell = cells.at(rand(), rand());
        if (!cell->objectInCell)
            AssignItem(cell);
    }
}

std::unordered_set<Collectable*> RegionMap::GetNearbyCollectables(const Cell* const cell, const int radius) const
{
    // todo phi: get cells in occupied region
    // need a mechanism to deal with boundaries

    // given a cell, get its region, then return all collectables in that region
    if (radius < 0)
    {
        Ordinal dir = GetRegion(cell);
        auto result = collectables.find(dir);
        if (result != collectables.end())
            return result->second;
        return {};
    }



    return {};
    // int x = cell->pos->x;
    // int y = cell->pos->y;
    // int mid = width/2;

}