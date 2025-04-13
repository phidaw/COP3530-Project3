#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include "../../Graph/Cell.h"
#include "../../Graph/Position.h"
#include "../../Maze/Maze.h"
#include "../../Tools/Array2D/CellArray2D.h"

using std::vector;
using std::queue;
using std::unordered_map;

class A_Star
{
    template <typename T>
    class PriorityQueue
    {
        typedef std::pair<int, Cell*> node;
        std::priority_queue<node, vector<node>, std::greater<>> pq;
    public:
        PriorityQueue() {}
        PriorityQueue(T item, int priority) : pq(std::make_pair(priority, item)) {}

        bool empty() const { return pq.empty(); }
        void insert(T item, int priority) { pq.emplace(priority, item); }
        T top()
        {
            T item = pq.top().second;
            pq.pop();
            return item;
        }
    };

    static int ManhattanDistance(Position* p1, Position* p2);

    static bool CheckIfBlocked(Cell* from, Cell* to, const Maze& maze);

    static void Search(Maze& maze, Cell* start, Cell* end, CellArray2D& cameFrom,
                       unordered_map<Cell*, int>& costSoFar);

    static vector<Cell*> FindPath(Maze& maze, Cell* start, Cell* end) ;
};