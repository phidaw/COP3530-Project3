#pragma once
#include <queue>
#include <vector>
#include "../../Graph/Cell.h"

template <typename T>
    class MinHeap
{
    typedef std::pair<int, Cell*> node;
    std::priority_queue<node, vector<node>, std::greater<>> pq;
public:
    MinHeap() {}
    MinHeap(T item, int priority)
    {
        pq.emplace(priority, item);
    }

    bool empty() const { return pq.empty(); }
    void insert(T item, int priority) { pq.emplace(priority, item); }
    T extract()
    {
        T item = pq.top().second;
        pq.pop();
        return item;
    }
};