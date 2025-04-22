#include <vector>
#include <cmath>
#include "../../Graph/Cell.h"
#include "RadixHeapTriple.h"

// ----------------------------------------- Private Functions -----------------------------------------

int RadixHeapTriple::HighestBit(int value)
{
    // when value is 0, key and last deleted differed in 0th bit
    // return -1 so that kth bucket is 0th bucket
    return value == 0 ? -1 : trunc(log2(value));
}

int RadixHeapTriple::GetBucketNum(int key) const
{
    // get the (k-1)th bit where the key and lastDeleted differ
    // then add +1 to get the index of the kth bucket
    return HighestBit(key ^ lastDeleted) + 1;
}

void RadixHeapTriple::CalculateLowestOccupiedBucket()
{
    lowestOccupiedBucket = -1;
    for (int i = 0; i < bucketCount; i++)
    {
        if (!buckets[i].empty())
        {
            lowestOccupiedBucket = i;
            break;
        }
    }
}

void RadixHeapTriple::Insert(Triple&& triple)
{
    // so long as this is called when redistributing a bucket's elements,
    // the given Triple's key will never be less than lastDeleted

    int bucketNum = GetBucketNum(triple.first());
    buckets[bucketNum].push_back(std::move(triple));
    if (lowestOccupiedBucket < 0 || bucketNum < lowestOccupiedBucket)
        lowestOccupiedBucket = bucketNum;
}

// ----------------------------------------- Public Functions -----------------------------------------

RadixHeapTriple::RadixHeapTriple(unsigned int maxKeyValue): elementCount(0), bucketCount(log2(maxKeyValue) + 1)
{
    buckets = new Bucket[bucketCount];
}

RadixHeapTriple::~RadixHeapTriple()
{
    delete[] buckets;
}

bool RadixHeapTriple::Empty() const
{
    return lowestOccupiedBucket < 0;
}

void RadixHeapTriple::Insert(int k1, int k2, Cell* value)
{
    // to maintain monotone invariant, we cannot store keys smaller than lastDeleted
    if (k1 < lastDeleted)
        return;

    elementCount++;
    int bucketNum = GetBucketNum(k1);
    buckets[bucketNum].emplace_back(k1, k2, value);
    if (lowestOccupiedBucket < 0 || bucketNum < lowestOccupiedBucket)
        lowestOccupiedBucket = bucketNum;
}

Cell* RadixHeapTriple::ExtractMin()
{
    if (Empty()) return nullptr;

    // get first non-empty bucket
    Bucket& b = buckets[lowestOccupiedBucket];

    // get Triple with minimal priority
    int kvpIndex = 0;
    Triple* prev = &b[kvpIndex];
    for (int i = 1; i < b.size(); i++)
    {
        int k1 = b[i].first();
        int k2 = b[i].second();
        // update min. if curr first priority is lower in value
        // otherwise, if they're equal compare second priority
        if (k1 < prev->first() || k1 == prev->first() && k2 < prev->second())
        {
            prev = &b[i];
            kvpIndex = i;
        }
    }

    // create copy of min element
    auto min = *prev;
    // extract minimal Triple
    b.erase(b.begin() + kvpIndex);
    elementCount--;

    // if lastDeleted is the same value as newly deleted,
    // there's no need to redistribute the bucket's elements (if any)
    if (lastDeleted == min.first())
    {
        if (b.empty())
            CalculateLowestOccupiedBucket();
        return min.third();
    }

    lastDeleted = min.first();

    // redistribute items using new lastDeleted
    int size = b.size();
    while (!b.empty())
    {
        Insert(std::move(b[0]));
        b.erase(b.begin());
    }

    // if there were no elements to redistribute...
    if (size == 0)
        CalculateLowestOccupiedBucket();

    return min.third();
}