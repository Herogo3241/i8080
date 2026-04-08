#pragma once
#include <cstdint>

namespace i8080::core {
    class Memory {
    public:
        uint8_t data[65536];

        Memory();

        uint8_t read(uint16_t addr) const;
        void write(uint16_t addr, uint8_t val);
    };
} // namespace i8080::memory
