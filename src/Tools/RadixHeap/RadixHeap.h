#pragma once
#include <vector>
#include <cmath>
#include "../../Graph/Cell.h"

class RadixHeap
{
    typedef std::pair<int, Cell*> Element;
    typedef std::vector<Element> Bucket;

    int numBuckets;
    int lastDeleted = 0;
    int lowestOccupiedBucket = -1;
    Bucket* buckets;

    static int HighestBit(int value);
    int GetBucketNum(int key) const;
    void CalculateLowestOccupiedBucket();
    void Insert(Element&& element);

public:
    RadixHeap(unsigned int maxKeyValue);
    ~RadixHeap();

    bool Empty() const;
    void Insert(int key, Cell* value);
    Cell* ExtractMin();
};