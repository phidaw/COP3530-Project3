#include <iostream>
#include "../AgentManager.h"
#include "../AStarAgent.h"
#include "../../../Maze/Maze.h"

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

int main()
{
    Maze maze(30);
    AStarAgent a1(maze.start);
    AgentManager manager;

    manager.AddAgent(a1);

    while (manager.HasAgents())
    {
        manager.RunAgents(maze, TraversalAgent::Mode::collecting);
    }
    cout << "\n-------------------- Stats --------------------\n";
    cout << a1.GetName() << " traveled " << a1.GetTotalDistanceTraveled() << " cells" << endl;
    cout << a1.GetName() << " collected: " << a1.GetTotalItemsCollected() << " of "
        << maze.graph.regionMap.GetTotalItemCount() << " items" << endl;

    return 0;
}