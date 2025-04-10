#include <stdexcept>
#include <random>
#include <chrono>
#include <unordered_map>
#include <tuple>
#include "Random.h"
using highResClock = std::chrono::high_resolution_clock;

// ----------------------------------- Static Re-declarations / Initializations -------------------------------------

// a new seed is used every time program runs, based on system's current time (relative to Jan. 1 1970)
std::mt19937 Random::mt(static_cast<std::mt19937::result_type>(
    highResClock::now().time_since_epoch().count())
);
std::mt19937 Random::mtDebug(DEFAULT_DEBUG_SEED);
Random::DistributionMap Random::savedDistributions;

// ------------------------------------------- Public Functions -------------------------------------------

// uses distribution with bounds from last setting
int Random::operator()(bool debug)
{
    return debug ? dist(mtDebug) : dist(mt);
}

// uses distribution with given bounds
int Random::operator()(int min, int max, bool debug) const
{
    if (min == max)
        return min;
    if (min > max)
        throw std::invalid_argument("Lower Distribution bound must be less than or equal to the Upper bound");

    KeyDouble t(min, max);

    // add new distribution with given bounds if not saved
    if (savedDistributions.count(t) == 0)
    {
        std::uniform_int_distribution<> d(min, max);
        savedDistributions.emplace(t, d);

        return debug ? d(mtDebug) : d(mt);
    }

    auto& d = savedDistributions[t];
    return debug ? d(mtDebug) : d(mt);
}

void Random::ChangeDebugSeed(const int newSeed)
{
    mtDebug.seed(newSeed);
}

// inclusive on both bounds
void Random::ChangeBounds(const int min, const int max)
{
    KeyDouble t(min, max);

    // add new distribution with given bounds if not saved
    if (savedDistributions.count(t) == 0)
    {
        dist = std::uniform_int_distribution<>(min, max);
        savedDistributions.emplace(t, dist);
    }
    else
        dist = savedDistributions[t];
}