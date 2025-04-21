#pragma once
#include <vector>
#include "../../Graph/Cell.h"

class RadixHeapDouble
{
    typedef std::pair<int, Cell*> Element;
    typedef std::vector<Element> Bucket;

    int lastDeleted = 0;
    int lowestOccupiedBucket = -1;
    int elementCount;
    int bucketCount;
    Bucket* buckets;

    static int HighestBit(int value);
    int GetBucketNum(int key) const;
    void CalculateLowestOccupiedBucket();
    void Insert(Element&& element);

public:
    RadixHeapDouble(unsigned int maxKeyValue);
    ~RadixHeapDouble();

    int Size() const { return elementCount; }
    bool Empty() const;
    void Insert(int key, Cell* value);
    Cell* ExtractMin();
};