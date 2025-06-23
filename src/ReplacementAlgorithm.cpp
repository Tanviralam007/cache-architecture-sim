#include "../include/ReplacementAlgorithm.h"
#include <cstdlib>

void RandomReplacement::SetWays(uint32_t numOfWays) {
    ways = static_cast<uint8_t>(numOfWays);
}

uint8_t RandomReplacement::GetVictim() const {
    if (ways == 0) {
        return 0; // No ways set, return 0
    }
    return static_cast<uint8_t>(rand() % ways);
}