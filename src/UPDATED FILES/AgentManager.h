#pragma once
#include <iostream>
#include <future>
#include <unordered_set>
#include <unordered_map>
#include <algorithm> // For sorting
#include "../../Graph/Cell.h"
#include "TraversalAgent.h"
#include "../Algorithms/Example/PrintAStar.h"
#include "../Toolbox.h"

class AgentManager
{
    std::unordered_set<TraversalAgent*> agents;
    std::unordered_map<TraversalAgent*, std::future<std::vector<Cell*>>> threads;
public:
    bool HasAgents() const { return !agents.empty(); }

    void AddAgent(TraversalAgent& agent)
    {
        agents.emplace(&agent);
    }
    void RemoveAgent(TraversalAgent& agent)
    {
        agents.erase(&agent);
        threads.erase(&agent);
    }

    void ResetAgentTimeCounters() const
    {
        for (auto* agent : agents)
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

        // Convert agents to a vector for sorting
        std::vector<TraversalAgent*> agentList(agents.begin(), agents.end());
        std::sort(agentList.begin(), agentList.end(), [](TraversalAgent* a, TraversalAgent* b) {
            // Order: A* -> BFS -> Dijkstra
            static const std::vector<std::string> order = {"A*", "BFS", "Dijkstra"};
            auto posA = std::find(order.begin(), order.end(), a->GetName());
            auto posB = std::find(order.begin(), order.end(), b->GetName());
            return posA < posB;
        });

        // Start a thread for each agent
        for (auto* agent : agentList)
        {
            threads[agent] = agent->CalculatePath(mode, maze);
        }

        // Process visuals while threads run
        for (auto* agent : agentList)
        {
            auto path = threads[agent].get();
            agent->Move(path, maze.end);
        }

        // Remove agents that exited the maze
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