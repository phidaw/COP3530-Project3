#include <unordered_set>
#include "Cell.h"
#include "Edge.h"
#include "Position.h"
#include "Graph.h"
#include "../Tools/Array2D/Array2D.h"

using namespace std;

void Graph::CreateVertices()
{
    for (int x = 0; x < nodesPerRow; x++)
    {
        for (int y = 0; y < nodesPerRow; y++)
            vertices.assign(x, y, new Position(x, y));
    }
}

void Graph::CreateCells()
{
    for (int x = 0; x < cells.Width(); x++)
    {
        for (int y = 0; y < cells.Height(); y++)
            cells.assign(x, y, new Cell(vertices, vertices.at(x, y)));
    }

    // assign adjacent cells after construction of all cells
    for (int x = 0; x < cells.Width(); x++)
    {
        for (int y = 0; y < cells.Height(); y++)
            cells.at(x, y)->AssignAdjacentCells(cells);
    }
}

void Graph::CreateEdges()
{
    // skipping last node to prevent adding a horizontal edge outside of graph
    int x = 0, y = 0;
    for (int i = 0; i < nodeNum-1; i++)
    {
        Position* n1 = vertices.at(x, y); // shared between horz and vert
        Position* h2 = x+1 < nodesPerRow ? vertices.at(x+1, y) : nullptr;
        Position* v2 = y+1 < nodesPerRow ? vertices.at(x, y+1) : nullptr;

        // only horizontal edges, if last row
        if (y == nodesPerRow-1)
        {
            Edge* edge = new Edge(n1, h2, Edge::Direction::Horizontal);
            edges.emplace(edge);
            // from cell at pos n1, go to the cell above it, and assign its bottom edge
            cells.at(n1->x, n1->y-1)->AssignEdge(edge);
        }
        // only vertical edges, if last column
        else if (x == nodesPerRow-1)
        {
            Edge* edge = new Edge(n1, v2, Edge::Direction::Vertical);
            edges.emplace(edge);
            // from cell at pos n1, go to left of cell, and assign its right edge
            cells.at(n1->x-1, n1->y)->AssignEdge(edge);
        }
        else
        {
            Edge* horEdge = new Edge(n1, h2, Edge::Direction::Horizontal);
            Edge* verEdge = new Edge(n1, v2, Edge::Direction::Vertical);
            edges.emplace(horEdge);
            edges.emplace(verEdge);
            cells.at(n1->x, n1->y)->AssignEdges(horEdge, verEdge);
        }

        x = ++x % nodesPerRow; // go to next column
        if (x == 0) y++; // go to next row
    }
}

Graph::Graph(int cellsPerRow) : cellsPerRow(cellsPerRow), cells(cellsPerRow, cellsPerRow),
                                cellNum(cellsPerRow * cellsPerRow), nodesPerRow(cellsPerRow + 1),
                                nodeNum(nodesPerRow * nodesPerRow),
                                vertices(nodesPerRow, nodesPerRow), regionMap(cellsPerRow)
{
    edgesPerType = cellsPerRow * nodesPerRow;
    edgeNum = edgesPerType * 2;

    CreateVertices();
    CreateCells();
    CreateEdges();

    regionMap.DistributeItems(cells);
}

Graph::~Graph()
{
    for (Edge* edge : edges)
        delete edge;
}

Cell* Graph::GetCell(int x, int y)
{
    if (x >= 0 && y >= 0 && x < cells.Size() && y < cells.Size())
        return cells.at(x, y);
    return nullptr;
}

Position* Graph::GetNode(int x, int y)
{
    if (x >= 0 && y >= 0 && x < vertices.Size() && y < vertices.Size())
        return vertices.at(x, y);
    return nullptr;
}

