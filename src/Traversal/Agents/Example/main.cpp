#include <iostream>
#include "../AgentManager.h"
#include "../AStarAgent.h"
#include "../BFSAgent.h"
#include "../DijkstraAgent.h"
#include "../../../Maze/Maze.h"
#include "../../../Maze/Example/PrintMaze.h"

using namespace std;

/** todo printing collectables to screen notes
 * printing collectables to screen
 * when printing cells to screen, if objectInCell != nullptr,
 * then also draw a collectable sprite inside the current cell
 */

/** Moving Agents
 * Create an agent manager
 * create agent objects for each algorithm and add to manager
 * in game loop,
     * call manager's RunAgents() and pass in a maze object and a mode
     * each agent's Move() will call some visuals code to print sprite(s) to screen
     *      (see UpdateVisuals() in each agent)
 */

void PrintStats(TraversalAgent& agent, Maze& maze);

int main()
{
    Maze maze(317);
    PrintMaze::Execute(maze, PrintMaze::Mode::maze);
    cout << "\n\n";

    AStarAgent aStar(maze.start);
    DijkstraAgent dijksta(maze.start);
    BFSAgent bfs(maze.start);

    AgentManager manager;
    manager.AddAgent(aStar);
    manager.AddAgent(dijksta);
    manager.AddAgent(bfs);

    // call this each time before running agents
    manager.ResetAgentTimeCounters();

    while (manager.HasAgents())
    {
        manager.RunAgents(maze, TraversalAgent::Mode::collecting);
    }

    cout << "\n-------------------- Stats --------------------\n";
    PrintStats(aStar, maze);
    PrintStats(dijksta, maze);
    PrintStats(bfs, maze);

    return 0;
}

void PrintStats(TraversalAgent& agent, Maze& maze)
{
    cout << agent.GetName() << "'s total execution time: " << agent.GetTotalTimeSpent() << "ms" << endl;
    cout << agent.GetName() << " traveled " << agent.GetTotalDistanceTraveled() << " cells" << endl;
    cout << agent.GetName() << " collected: " << agent.GetTotalItemsCollected() << " of "
        << maze.graph.regionMap.GetTotalItemCount() << " items" << "\n\n";
}