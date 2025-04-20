#pragma once
#include <random>
#include <unordered_map>
#include <tuple>

class Random
{
private:
    typedef std::tuple<int, int> KeyDouble;

    // A hash function used to hash a tuple
    struct key_hash
    {
        std::size_t operator()(const KeyDouble& k) const
        {
            // combine bits to create a hash code
            return std::get<0>(k) ^ std::get<1>(k);
        }
    };
    // equality comparator for defined tuple
    struct key_equal
    {
        bool operator()(const KeyDouble& v0, const KeyDouble& v1) const
        {
            return v0 == v1;
        }
    };

    typedef std::unordered_map<KeyDouble, std::uniform_int_distribution<>, key_hash, key_equal> DistributionMap;

    const static int DEFAULT_DEBUG_SEED = 0;
    const static int DEFAULT_LOWER_BOUND = 0;
    const static int DEFAULT_UPPER_BOUND = 20;

    static std::mt19937 mt;
    static std::mt19937 mtDebug;
    std::uniform_int_distribution<> dist;
    static DistributionMap savedDistributions;
public:
    Random(const int distLwr = DEFAULT_LOWER_BOUND, const int distUpr = DEFAULT_UPPER_BOUND)
        : dist(distLwr, distUpr)
    {
        savedDistributions.emplace(std::make_tuple(distLwr, distUpr), dist);
    }

    // uses distribution with bounds from last setting (the current dist)
    int operator()(bool debug = false);
    // uses distribution with given bounds
    int operator()(int min, int max, bool debug = false) const;

    void ChangeBounds(const int min, const int max);
    static void ChangeDebugSeed(const int newSeed);
};