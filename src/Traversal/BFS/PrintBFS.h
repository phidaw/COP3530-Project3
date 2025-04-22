#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "../../../../Maze/Maze.h"
#include "../BFS.h"

using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::right;

struct PrintBFS
{
    static void Execute(Maze& maze);
};

inline void PrintBFS::Execute(Maze& maze)
{
    string dirToStr[4] {"N", "E", "S", "W"};
    auto path = BFS::FindPath(maze, maze.start, maze.end);

    cout << "BFS start: " << maze.start->pos << endl;
    for (int i = 0; i < path.size(); i++)
    {
        if (i == path.size()-1)
            cout << "BFS end: " << right << setw(8) << path[i]->pos << endl;
        else
            cout << right << setw(15) << path[i]->pos << endl;
    }
}