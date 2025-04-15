#pragma once
#include <future>
#include "../../Maze/Maze.h"
#include "../Algorithms/A-star/A_Star.h"

struct TraversalAgent
{
    int val;
    vector<Cell*> path;

    enum Mode { traversal, collecting };
    virtual std::future<vector<Cell*>> Execute(Mode mode, Maze& maze) = 0;

    virtual ~TraversalAgent() = 0;
};

inline TraversalAgent::~TraversalAgent() {}

struct AStarAgent : public TraversalAgent
{
    // void ComplexTraversal()
    // {
    //
    // }
    std::future<vector<Cell*>> Execute(Mode mode, Maze& maze) override
    {
        if (mode == TraversalAgent::Mode::collecting)
        {
            // ...
        }

        // simple mode w/ no collectables, so no need to limit path
        // async policy ensures that this will run on a separate thread from main
        return std::async(std::launch::async,
            [&maze]()
            {
                return A_Star::FindPath(maze, maze.start, maze.end, false);
            });
    }
};