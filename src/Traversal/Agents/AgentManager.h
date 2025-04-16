#pragma once
#include <iostream>
#include <future>
#include <unordered_set>
#include <unordered_map>
#include "../../Graph/Cell.h"
#include "TraversalAgent.h"
#include "../Algorithms/A-star/Example/PrintAStar.h"

class AgentManager
{
    std::unordered_set<TraversalAgent*> agents;
    std::unordered_map<TraversalAgent*, std::future<vector<Cell*>> > threads;
public:

    bool HasAgents() const { return !agents.empty(); }

    // visuals call these
    void AddAgent(TraversalAgent& agent)
    {
        agents.emplace(&agent);
    }
    void RemoveAgent(TraversalAgent& agent)
    {
        agents.erase(&agent);
        threads.erase(&agent);
    }

    void RunAgents(Maze& maze, TraversalAgent::Mode mode = TraversalAgent::Mode::traversal)
    {
        // no agents to run
        if (agents.empty())
            return;

        // start a thread for each agent
        for (auto* agent : agents)
        {
            threads[agent] = agent->CalculatePath(mode, maze);
        }

        // process visuals while threads run
        for (auto& kvp : threads)
        {
            // wait for thread to finish, then get returned vector
            auto path = kvp.second.get();

            // move agent along path
            kvp.first->Move(path, maze.end);
        }

        // remove any agents that exited maze
        for (auto iter = agents.begin(); iter != agents.end();)
        {
            if ((*iter)->CheckIfExitedMaze())
            {
                std::cout << "------------ " << (*iter)->GetName() << " exited the maze ------------" << std::endl;
                threads.erase(*iter);
                iter = agents.erase(iter);
            }
            else
                ++iter;
        }
    }
};