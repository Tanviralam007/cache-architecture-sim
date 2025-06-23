#ifndef REPLACEMENT_ALGORITHM_H
#define REPLACEMENT_ALGORITHM_H

#include <cstdint>

class RandomReplacement{
    public:
        void SetWays(uint32_t numOfWays);
        uint8_t GetVictim() const;

    private:
        uint8_t ways = 0; // Number of ways in the cache
};

#endif