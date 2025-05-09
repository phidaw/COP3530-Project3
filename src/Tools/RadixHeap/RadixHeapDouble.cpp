#include <vector>
#include <cmath>
#include "../../Graph/Cell.h"
#include "RadixHeapDouble.h"

// ----------------------------------------- Private Functions -----------------------------------------

int RadixHeapDouble::HighestBit(int value)
{
    // when value is 0, key and last deleted differed in 0th bit
    // return -1 so that kth bucket is 0th bucket
    return value == 0 ? -1 : trunc(log2(value));
}

int RadixHeapDouble::GetBucketNum(int key) const
{
    // get the (k-1)th bit where the key and lastDeleted differ
    // then add +1 to get the index of the kth bucket
    return HighestBit(key ^ lastDeleted) + 1;
}

void RadixHeapDouble::CalculateLowestOccupiedBucket()
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

void RadixHeapDouble::Insert(Element&& element)
{
    // so long as this is called when redistributing a bucket's elements,
    // the given element's key will never be less than lastDeleted

    int bucketNum = GetBucketNum(element.first);
    buckets[bucketNum].push_back(std::move(element));
    if (lowestOccupiedBucket < 0 || bucketNum < lowestOccupiedBucket)
        lowestOccupiedBucket = bucketNum;
}

// ----------------------------------------- Public Functions -----------------------------------------

RadixHeapDouble::RadixHeapDouble(unsigned int maxKeyValue): elementCount(0), bucketCount(log2(maxKeyValue) + 1)
{
    buckets = new Bucket[bucketCount];
}

RadixHeapDouble::~RadixHeapDouble()
{
    delete[] buckets;
}

bool RadixHeapDouble::Empty() const
{
    return lowestOccupiedBucket < 0;
}

void RadixHeapDouble::Insert(int key, Cell* value)
{
    // to maintain monotone invariant, we cannot store keys smaller than lastDeleted
    if (key < lastDeleted)
        return;

    elementCount++;
    int bucketNum = GetBucketNum(key);
    buckets[bucketNum].emplace_back(key, value);
    if (lowestOccupiedBucket < 0 || bucketNum < lowestOccupiedBucket)
        lowestOccupiedBucket = bucketNum;
}

Cell* RadixHeapDouble::ExtractMin()
{
    if (Empty()) return nullptr;

    // get first non-empty bucket
    Bucket& b = buckets[lowestOccupiedBucket];

    // get element with minimal priority
    int kvpIndex = 0;
    int minKey = b[kvpIndex].first;
    for (int i = 1; i < b.size(); i++)
    {
        int key = b[i].first;
        if (key < minKey)
        {
            minKey = key;
            kvpIndex = i;
        }
    }

    // create copy of min element
    auto p = b[kvpIndex];
    // extract minimal element
    b.erase(b.begin() + kvpIndex);
    elementCount--;

    // if lastDeleted is the same value as newly deleted,
    // there's no need to redistribute the bucket's elements (if any)
    if (lastDeleted == p.first)
    {
        if (b.empty())
            CalculateLowestOccupiedBucket();
        return p.second;
    }

    lastDeleted = p.first;

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

    return p.second;
}