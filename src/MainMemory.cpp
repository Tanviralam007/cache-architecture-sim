#include "../include/MainMemory.h"
#include <array>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>

MainMemory::MainMemory() {
    memory = std::make_unique<std::array<uint8_t, MAIN_MEMORY_SIZE>>();
    memory.get()->fill(0x00);
}

MainMemory::~MainMemory() {
    
}

void MainMemory::Read(uint32_t startAddress, uint8_t size, uint8_t* destination) {
    std::memcpy(destination, &memory.get()->at(startAddress), size);
}

void MainMemory::Write(uint32_t startAddress, uint8_t size, uint8_t* source) {
    std::memcpy(&memory.get()->at(startAddress), source, size);
}

void MainMemory::Print() {
    const uint32_t ROWS = 24;
    const uint32_t COLUMNS = 12;

    for (uint32_t row = 0; row < ROWS; ++row) {
        for (uint32_t column = 0; column < COLUMNS; ++column) {
            uint8_t value = memory->at(row * COLUMNS + column);
            
            std::stringstream ss;
            ss << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
            std::cout << ss.str() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (uint8_t dash = 0; dash < COLUMNS * 3; ++dash) {
        std::cout << "-";
    }
}