#include "memory.hpp"

namespace i8080::core
{
    Memory::Memory() {}

    uint8_t Memory::read(uint16_t addr) const {
        return data[addr];
    }

    void Memory::write(uint16_t addr, uint8_t val) {
        data[addr] = val;
    }

} // namespace i8080::memory
