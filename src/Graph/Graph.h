#pragma once
#include <unordered_set>
#include "../Tools/Array2D/Array2D.h"
#include "../Tools/Array2D/CellArray2D.h"
#include "RegionMap.h"
#include "Cell.h"

using std::unordered_set;

class Graph
{
    const static int DEFAULT_CELLS_PER_ROW = 4;
    int cellNum;
    int cellsPerRow;
    int nodesPerRow;
    int nodeNum;
    int edgeNum;
    int edgesPerType;

    void CreateVertices();
    void CreateCells();
    void CreateEdges();
public:
    Array2D<Position> vertices;
    CellArray2D cells;
    unordered_set<Edge*> edges;
    RegionMap regionMap;

    // construction / destruction
    Graph(int cellsPerRow = DEFAULT_CELLS_PER_ROW);
    ~Graph();

    // accessors
    Cell* GetCell(int x, int y);
    Position* GetNode(int x, int y);

    int GetCellNum() const { return cellNum; }
    int GetCellsPerRow() const { return cellsPerRow; }
    int GetNodeNum() const { return nodeNum; }
    int GetNodesPerRow() const { return nodesPerRow; }
    int GetEdgeNum() const { return edgeNum; }
    int GetEdgesPerType() const { return edgesPerType; }
};