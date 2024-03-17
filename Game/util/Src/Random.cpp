/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "Random.h"

#include <ctime>
#include <random>

namespace FA {

namespace Util {

class Random
{
public:
    Random()
        : rng_(static_cast<unsigned int>(std::time(nullptr)))
    {}

    int RandomizeRange(int min, int max)
    {
        std::uniform_int_distribution<unsigned int> rangeRandLen(min, max);
        return rangeRandLen(rng_);
    }

private:
    std::mt19937 rng_;
};

Random r;

int RandomizeRange(int min, int max)
{
    return r.RandomizeRange(min, max);
}

}  // namespace Util

}  // namespace FA
