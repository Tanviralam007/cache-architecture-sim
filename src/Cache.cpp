#include "../include/Cache.h"
#include "../include/ReplacementAlgorithm.h"
#include <iostream>
#include <cstring>
#include <iomanip>

CacheSet::CacheSet() {
    replacement.SetWays(CACHE_WAYS);
}

CacheSet::~CacheSet() {}

CacheLine* CacheSet::FindLine(uint32_t tag) {
    for (uint8_t ways = 0; ways < CACHE_WAYS; ++ways) {
        if (lines[ways].valid && lines[ways].tag == tag) {
            return &lines[ways];
        }
    }
    return nullptr;
}

CacheLine* CacheSet::Replace(uint32_t tag, uint8_t* sourceData) {
    //choose a victime line to replace]
    uint8_t victim = replacement.GetVictim();

    lines[victim].tag = tag;
    lines[victim].valid = true;

    //copy data from source to cache line
    std::memcpy(lines[victim].data.data(), sourceData, CACHE_LINE_SIZE);
    return &lines[victim];
}

void Cache::initialize(MainMemory* memory) {
    mainMemory = memory;
}

uint32_t Cache::Read(uint32_t address) {
    AddressParts parts(address);
    
    CacheLine* line = sets[parts.setIndex].FindLine(parts.tag);

    if (line) {
        std::string message = "Cache hit for address: 0x" + 
            std::to_string(address) + " in set: " + 
            std::to_string(parts.setIndex) + " with tag: " + 
            std::to_string(parts.tag);
        std::cout << message << std::endl;

        // Cache hit
        return *reinterpret_cast<uint32_t*>(&line->data[parts.byteOffset]);
    } else {
        // Cache miss
        // find the beginnning of the cache line
        uint32_t lineStart = address & ~(CACHE_LINE_SIZE - 1);
        // allocate a buffer to hold the data
        std::array<uint8_t, CACHE_LINE_SIZE> buffer;
        // read the requested data from main memory
        mainMemory->Read(lineStart, CACHE_LINE_SIZE, buffer.data());
        // replace the cache line
        CacheLine* newLine = sets[parts.setIndex].Replace(parts.tag, buffer.data());
        // reinterpret the data as uint32_t and return the requested data
        return *reinterpret_cast<uint32_t*>(&newLine->data[parts.byteOffset]);
    }
    return 0;
}

void Cache::Write(uint32_t address, uint32_t data) {
    AddressParts parts(address);
    
    CacheLine* line = sets[parts.setIndex].FindLine(parts.tag);

    if (line) {
        std::string message = "Cache hit for address: 0x" + 
            std::to_string(address) + " in set: " + 
            std::to_string(parts.setIndex) + " with tag: " + 
            std::to_string(parts.tag);
        std::cout << message << std::endl;
        
        // Cache hit
        *reinterpret_cast<uint32_t*>(&line->data[parts.byteOffset]) = data;
    }

    // Cache miss
    // write through cache (immediately write to main memory)
    mainMemory->Write(address, sizeof(uint32_t), reinterpret_cast<uint8_t*>(&data));
}
