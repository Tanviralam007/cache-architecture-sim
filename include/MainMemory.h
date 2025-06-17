#include <memory>

const uint32_t MAIN_MEMORY_SIZE = 4 * 1024 * 1024; // 4 MB as defined in the original code

class MainMemory {
    public:
        MainMemory();
        ~MainMemory();

        void Read(uint32_t startAddress, uint8_t size, uint8_t* destination);
        void Write(uint32_t startAddress, uint8_t size, uint8_t* source);
        void Print();

    private:
        std::unique_ptr<std::array<uint8_t, MAIN_MEMORY_SIZE>> memory;
};