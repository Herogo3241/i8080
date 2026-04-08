#pragma once
#include <cstdint>

namespace i8080::core {
    class Memory {
    private:
        uint8_t data[65536];
        
    public:
        Memory();

        uint8_t read(uint16_t addr) const;
        void write(uint16_t addr, uint8_t val);
        const uint8_t* get_all_data() const;
    };
} // namespace i8080::memory
