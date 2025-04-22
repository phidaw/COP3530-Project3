#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "../../../Maze/Maze.h"
#include "../../../Graph/Cell.h"
#include "../A-star/A_Star.h"

using std::cout;
using std::endl;
using std::setw;
using std::right;
using std::vector;

struct PrintAStar
{
    static void Execute(Maze& maze, bool limitPath, vector<Cell*> path = {});
};

inline void PrintAStar::Execute(Maze& maze, bool limitPath, vector<Cell*> path)
{
    path = !path.empty() ? path : A_Star::FindPath(maze, maze.start, maze.end, limitPath);

    cout << "A* start: " << maze.start->pos << endl;
    for (int i = 0; i < path.size(); i++)
    {
        if (i == path.size()-1)
            cout << "A* end: " << right << setw(8) << path[i]->pos << endl;
        else
            cout << right << setw(13) << path[i]->pos << endl;
    }
}