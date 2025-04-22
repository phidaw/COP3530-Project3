#include <iostream>
#include "PrintMaze.h"
#include "../Maze.h"

using namespace std;

int main()
{
    int cellsPerRow = 317;
    Maze maze(cellsPerRow);
    PrintMaze::Execute(maze, PrintMaze::maze);
    cout << "\nmaze size: " << cellsPerRow << "x" << cellsPerRow << endl;
    return 0;
}