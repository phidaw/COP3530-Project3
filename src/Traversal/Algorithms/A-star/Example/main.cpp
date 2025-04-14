#include <iostream>
#include "../../../../Maze/Maze.h"
#include "../../../../Maze/Example/PrintMaze.h"
#include "PrintAStar.h"

using namespace std;

int main()
{
    int cellsPerRow = 10;
    PrintMaze::Mode mode = PrintMaze::maze;

    Maze maze(cellsPerRow);
    PrintMaze::Execute(maze, mode);
    cout << endl;
    PrintAStar::Execute(maze);

    return 0;
}