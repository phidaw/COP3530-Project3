#pragma once
#include <iomanip>
#include <iostream>
#include "../Maze.h"

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;

struct PrintMaze
{
    enum Mode { maze, graph };

    static void PrintHorizontalEdge(bool val)
    {
        if (val)
            cout << right << setw(4) << "---";
        else
            cout << left << setw(4) << "";
    }
    static void PrintVerticalEdge(bool val)
    {
        if (val)
            cout << left << setw(4) << "|";
        else
            cout << left << setw(4) << "";
    }

    static void Execute(Maze& maze, Mode mode)
    {
        auto& walls = mode == Mode::maze ? maze.walls : maze.graph.edges;
        auto& cells = maze.graph.cells;

        int cellNum = maze.graph.GetCellNum();
        int cellPerRow = maze.graph.GetCellsPerRow();
        int vertPerRow = maze.graph.GetNodesPerRow();

        // cell at current pos, print its left and top edges (if in maze walls)
        // during last col, also print right
        // during last row, print just the top
        int x = 0, y = 0;
        vector<bool> verticalEdges(vertPerRow);
        for (int i = 0; i < cellNum; i++)
        {
            auto* cell = cells.at(x, y);
            auto* topEdge = cell->edges[Cell::CardinalDir::North];
            auto* leftEdge = cell->edges[Cell::CardinalDir::West];
            auto* rightEdge = cell->edges[Cell::CardinalDir::East];

            // last column
            if (x == cellPerRow-1)
            {
                if (walls.count(topEdge) != 0)
                    PrintHorizontalEdge(true);
                else
                    PrintHorizontalEdge(false);

                if (walls.count(leftEdge) != 0)
                    verticalEdges[x] = true;
                else
                    verticalEdges[x] = false;

                if (walls.count(rightEdge) != 0)
                    verticalEdges[x+1] = true;
                else
                    verticalEdges[x+1] = false;
            }
            else
            {
                if (walls.count(topEdge) != 0)
                    PrintHorizontalEdge(true);
                else
                    PrintHorizontalEdge(false);

                if (walls.count(leftEdge) != 0)
                    verticalEdges[x] = true;
                else
                    verticalEdges[x] = false;
            }

            x = ++x % cellPerRow; // go to next cell column
            if (x == 0)
            {
                // print vert edges from last row
                if (!verticalEdges.empty())
                {
                    cout << endl;
                    for (bool v : verticalEdges)
                        PrintVerticalEdge(v);
                    cout << endl;
                    verticalEdges.clear();
                    verticalEdges.resize(vertPerRow);
                }

                // print final row of horizontal edges
                if (i == cellNum-1)
                {
                    for (int k = 0; k < cellPerRow; k++)
                    {
                        auto* c = cells.at(k, y);

                        auto* botEdge = c->edges[Cell::CardinalDir::South];

                        if (walls.count(botEdge) != 0)
                            PrintHorizontalEdge(true);
                        else
                            PrintHorizontalEdge(false);
                    }

                    break;
                }

                // go to next row
                y++;
            }
        }
    }
};