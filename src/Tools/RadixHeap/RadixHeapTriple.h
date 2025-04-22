#pragma once
#include <vector>
#include <tuple>
#include "../../Graph/Cell.h"

class RadixHeapTriple
{
    struct Triple
    {
        std::tuple<int, int, Cell*> data;
        Triple(int k1, int k2, Cell* value) :
            data(k1, k2, value) {}

        int first() { return std::get<0>(data); }
        int second() { return std::get<1>(data); }
        Cell* third() { return std::get<2>(data); }
    };
    typedef std::vector<Triple> Bucket;

    int lastDeleted = 0;
    int lowestOccupiedBucket = -1;
    int elementCount;
    int bucketCount;
    Bucket* buckets;

    static int HighestBit(int value);
    int GetBucketNum(int key) const;
    void CalculateLowestOccupiedBucket();
    void Insert(Triple&& element);

public:
    RadixHeapTriple(unsigned int maxKeyValue);
    ~RadixHeapTriple();

    int Size() const { return elementCount; }
    bool Empty() const;
    void Insert(int k1, int k2, Cell* value);
    Cell* ExtractMin();
};