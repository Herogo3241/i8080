#pragma once
#include <cstdint>
#include "../memory/memory.hpp"

namespace i8080::core {
    class CPU {
    private:
        Memory& mem;
    public:
        uint8_t A, B, C, D, E, H, L;  // main registers + accumulator(A)
        struct Flags {
            bool S;   // Sign flag
            bool Z;   // Zero flag
            bool AC;  // Auxillary Carry
            bool P;   // Parity Flag
            bool C;   // Carry Flag

            uint8_t to_byte() const {
                return (S << 7) | (Z << 6) | (0 << 5) | (AC << 4) | (0 << 3) | (P << 2) |
                    (1 << 1) | C;
            }

            void from_byte(uint8_t flag) {
                S = (flag >> 7) & 1;
                Z = (flag >> 6) & 1;
                AC = (flag >> 4) & 1;
                P = (flag >> 2) & 1;
                C = flag & 1;
            }
        } flags;

        uint16_t SP; //stack pointer
        uint16_t PC; // program counter
        


        uint16_t BC() const { return (static_cast<uint16_t>(B) << 8) | C; }

        void set_BC(uint16_t val) {
            B = (val >> 8) & 0xFF;
            C = val & 0xFF;
        }

        uint16_t DE() const { return (static_cast<uint16_t>(D) << 8) | E; }

        void set_DE(uint16_t val) {
            D = (val >> 8) & 0xFF;
            E = val & 0xFF;
        }

        uint16_t HL() const { return (static_cast<uint16_t>(H) << 8) | L; }

        void set_HL(uint16_t val) {
            H = (val >> 8) & 0xFF;
            L = val & 0xFF;
        }

        // program status word (A + Flags)
        uint16_t PSW() const {
            return (static_cast<uint16_t>(A) << 8) | flags.to_byte();
        }

        void set_PSW(uint16_t val) {
            A = (val >> 8) & 0xFF;
            flags.from_byte(val & 0xFF);
        }

        CPU(Memory& memory_ref); 
        ~CPU();
    };
}  // namespace i8080::core
