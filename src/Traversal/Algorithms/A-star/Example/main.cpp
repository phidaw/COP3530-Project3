#include <iostream>
#include "../../../../Maze/Maze.h"
#include "../../../../Maze/Example/PrintMaze.h"
#include "PrintAStar.h"

using namespace std;

int main()
{
    int cellsPerRow = 3;
    bool limitPath = false;
    PrintMaze::Mode mode = PrintMaze::maze;

    Maze maze(cellsPerRow);
    PrintMaze::Execute(maze, mode);
    cout << endl;
    PrintAStar::Execute(maze, limitPath);

    return 0;
}