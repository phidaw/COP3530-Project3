#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "../../../../Maze/Maze.h"
#include "../Dijkstra.h"

using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::right;

struct PrintDijkstra
{
    static void Execute(Maze& maze, const vector<Cell*>& targets);
};

inline void PrintDijkstra::Execute(Maze& maze, const vector<Cell*>& targets)
{
    string dirToStr[4] {"N", "E", "S", "W"};
    auto path = Dijkstra::FindPath(maze, maze.start, targets);

    cout << "Dijkstra start: " << maze.start->pos << endl;
    for (int i = 0; i < path.size(); i++)
    {
        if (i == path.size()-1)
            cout << "Dijkstra end: " << right << setw(8) << path[i]->pos << endl;
        else
            cout << right << setw(18) << path[i]->pos << endl;
    }
}