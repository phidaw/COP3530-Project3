#pragma once
#include <unordered_set>
#include <unordered_map>
#include "Cell.h"
#include "Collectable.h"
#include "../Tools/Array2D/CellArray2D.h"
#include "../Tools/CompassDir/CompassDir.h"
#include "../Tools/Random/Random.h"

class RegionMap
{
    Random rand;
    int collectableCount = 0;
    std::unordered_map<Ordinal, std::unordered_set<Collectable*>> collectables;
public:
    const int width;

    RegionMap(const int w) : width(w) {}
    ~RegionMap();

    Ordinal GetRegion(const Cell* const cell) const;
    void AssignItem(Cell* cell);
    void DistributeItems(CellArray2D& cells);
    std::unordered_set<Collectable*> GetNearbyCollectables(const Cell* const cell, const int radius = -1) const;
    int GetTotalItemCount() const { return collectableCount; }
};