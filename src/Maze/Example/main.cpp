#include <iostream>
#include "PrintMaze.h"
#include "../Maze.h"

using namespace std;

int main()
{
    Maze maze(317);
    PrintMaze::Execute(maze, PrintMaze::maze);

    return 0;
}