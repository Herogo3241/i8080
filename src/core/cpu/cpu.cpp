#include "cpu.hpp"

namespace i8080::core{
    CPU::CPU(Memory& memory_ref) : A(0), B(0), C(0), D(0), E(0), H(0), L(0), mem(memory_ref) {
        pc = 0;
        sp = 0;
    }

    CPU::~CPU() {}
}


