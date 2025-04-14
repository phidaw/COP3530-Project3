#include <iostream>
#include "PrintMaze.h"
#include "../Maze.h"

using namespace std;

int main()
{
    int cellsPerRow = 4;
    PrintMaze::Mode mode = PrintMaze::maze;
    int mazeNum = 1;

    for (int i = 0; i < mazeNum; i++)
    {
        Maze maze(cellsPerRow);
        PrintMaze::Execute(maze, mode);
        cout << "\n\n\n";
    }

    return 0;
}