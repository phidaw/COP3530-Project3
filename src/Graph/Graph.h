#pragma once
#include <unordered_set>
#include "../Tools/Array2D/Array2D.h"
#include "Cell.h"

using std::unordered_set;

// https://stackoverflow.com/questions/8526819/c-header-files-including-each-other-mutually
class Cell;

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
    Array2D<Cell> cells;
    Array2D<Position> vertices;
    unordered_set<Edge*> edges;

    // construction / destruction
    Graph(int cellsPerRow = DEFAULT_CELLS_PER_ROW);
    ~Graph();

    // accessors
    Cell* GetCell(int x, int y);
    Position* GetNode(int x, int y);
    // unordered_set<Edge*> GetInnerEdges() const;

    int GetCellNum() const { return cellNum; }
    int GetCellsPerRow() const { return cellsPerRow; }
    int GetNodeNum() const { return nodeNum; }
    int GetNodesPerRow() const { return nodesPerRow; }
    int GetEdgeNum() const { return edgeNum; }
    int GetEdgesPerType() const { return edgesPerType; }
};