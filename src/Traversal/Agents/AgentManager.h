#pragma once
#include <iostream>
#include <future>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include "../../Graph/Cell.h"
#include "TraversalAgent.h"
#include "../Algorithms/Example/PrintAStar.h"

class AgentManager
{
    std::unordered_set<std::unique_ptr<TraversalAgent>> agents;
    std::unordered_map<TraversalAgent*, std::future<std::vector<Cell*>>> threads;

public:
    bool HasAgents() const { return !agents.empty(); }

    // Add a dynamically allocated agent, taking ownership
    void AddAgent(std::unique_ptr<TraversalAgent> agent)
    {
        TraversalAgent* agentPtr = agent.get();
        agents.emplace(std::move(agent));
        threads[agentPtr]; // Initialize thread entry
    }

    // Remove an agent by pointer
    void RemoveAgent(TraversalAgent* agent)
    {
        auto it = std::find_if(agents.begin(), agents.end(),
            [agent](const auto& ptr) { return ptr.get() == agent; });
        if (it != agents.end()) {
            agents.erase(it);
            threads.erase(agent);
        }
    }

    void ResetAgentTimeCounters() const
    {
        for (const auto& agent : agents)
            agent->ResetTimeCounter();
    }

    void Reset()
    {
        agents.clear();
        threads.clear();
    }

    void RunAgents(Maze& maze, TraversalAgent::Mode mode = TraversalAgent::Mode::traversal)
    {
        if (agents.empty())
            return;

        for (const auto& agent : agents)
        {
            threads[agent.get()] = agent->CalculatePath(mode, maze);
        }

        for (auto& kvp : threads)
        {
            auto path = kvp.second.get();
            kvp.first->Move(path, maze.end);
        }

        for (auto iter = agents.begin(); iter != agents.end();)
        {
            if ((*iter)->CheckIfExitedMaze())
            {
                std::cout << "------------ " << (*iter)->GetName() << " exited the maze ------------" << std::endl;
                threads.erase(iter->get());
                iter = agents.erase(iter);
            }
            else
                ++iter;
        }
    }
};
