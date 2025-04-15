#pragma once
#include <iostream>
#include <future>
#include <unordered_set>
#include <unordered_map>
#include "../../Graph/Cell.h"
#include "TraversalAgent.h"
#include "../Algorithms/A-star/Example/PrintAStar.h"

struct AgentManager
{
    std::unordered_set<TraversalAgent*> agents;
    std::unordered_map<TraversalAgent*, std::future<vector<Cell*>> > threads;

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

    void RunAgents(Maze& maze)
    {
        // start a thread for each agent
        for (auto* agent : agents)
        {
            threads[agent] = agent->Execute(TraversalAgent::Mode::traversal, maze);
        }

        // process visuals while threads run
        for (auto& kvp : threads)
        {
            // wait for thread to finish, then get returned vector
            auto path = kvp.second.get();

            // perform actions relative to current agent
            // update GUI

            // test print
            PrintAStar::Execute(maze, false, path);
        }
    }
};
