#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "../../../../Maze/Maze.h"
#include "../A_Star.h"

using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::right;

struct PrintAStar
{
    static void Execute(Maze& maze);
};

inline void PrintAStar::Execute(Maze& maze)
{
    string dirToStr[4] {"N", "E", "S", "W" };
    auto path = A_Star::FindPath(maze, maze.start, maze.end);

    cout << "start: " << maze.start->pos << endl;
    for (int i = 0; i < path.size(); i++)
    {
        if (i == path.size()-1)
            cout << "end: " << right << setw(8) << path[i]->pos << endl;
        else
            cout << right << setw(13) << path[i]->pos << endl;
    }
}