#ifndef CACHE_H
#define CACHE_H

#include "../include/MainMemory.h"
#include "../include/ReplacementAlgorithm.h"
#include <array>

const uint8_t MEMORY_ADDRESS_SIZE = 32;
const uint8_t CACHE_LINE_SIZE = 64;
const uint32_t CACHE_SETS = 64;
const uint32_t CACHE_WAYS = 4;


const uint8_t CACHE_LINE_BYTE_OFFSET_SIZE = 6; // log2(CACHE_LINE_SIZE)
const uint8_t CACHE_LINE_SET_INDEX_SIZE = 6; // log2(CACHE_SETS)
const uint8_t CACHE_LINE_TAG_SIZE = 20;  

struct CacheLine {
    uint32_t tag = 0;
    std::array<uint8_t, CACHE_LINE_SIZE> data;
    bool valid = false;
};

struct AddressParts {
    uint32_t tag = 0;
    uint32_t setIndex = 0;
    uint32_t byteOffset = 0;

    AddressParts(uint32_t address) {
        byteOffset = address & (CACHE_LINE_SIZE - 1);
        setIndex = (address >> CACHE_LINE_BYTE_OFFSET_SIZE) & ((1 << CACHE_LINE_SET_INDEX_SIZE) - 1);
        tag = address >> (CACHE_LINE_BYTE_OFFSET_SIZE + CACHE_LINE_SET_INDEX_SIZE);
    }
};

class CacheSet{
    public:
        CacheSet();
        ~CacheSet();

        CacheLine* FindLine(uint32_t tag);
        CacheLine* Replace(uint32_t tag, uint8_t* sourceData);

    private:
        std::array<CacheLine, CACHE_WAYS> lines;
        RandomReplacement replacement;

};

class Cache {
    private:
        std::array<CacheSet, CACHE_SETS> sets;
        MainMemory* mainMemory;

    public:
        void initialize(MainMemory* memory);
        uint32_t Read(uint32_t address);
        void Write(uint32_t address, uint32_t data);
};

#endif