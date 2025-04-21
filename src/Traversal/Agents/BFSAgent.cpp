#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"
#include "AStarAgent.h"
#include "BFSAgent.h"

void BFSAgent::UpdateVisuals()
{
    // todo -- update GUI here --
    // use this->currCell
}

std::future<vector<Cell*>> BFSAgent::CalculatePath(Mode mode, Maze& maze)
{
    if (mode == TraversalAgent::Mode::collecting)
    {
        // async policy ensures that this will run on a separate thread from main
        return std::async(std::launch::async,
            [this, &maze]()
            {
                Cell* target = CalculateUtility(maze);

                // todo: replace A_Star with BFS
                return A_Star::FindPath(maze, currCell, target);
            });
    }

    // simple mode w/ no collectables, so no need to limit path
    return std::async(std::launch::async,
        [&maze]()
        {
            // todo: replace A_Star with BFS
            return A_Star::FindPath(maze, maze.start, maze.end);
        });
}