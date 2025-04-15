#include "../AgentManager.h"
#include "../TraversalAgent.h"
#include "../../../Maze/Maze.h"

int main()
{
    Maze maze(2);
    AStarAgent a1;
    AStarAgent a2;
    AStarAgent a3;
    AgentManager manager;

    manager.AddAgent(a1);
    manager.AddAgent(a2);
    manager.AddAgent(a3);

    manager.RunAgents(maze);
    manager.RemoveAgent(a3);
    manager.RunAgents(maze);

    return 0;
}