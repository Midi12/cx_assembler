#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("JMP instructions are assembled correctly", "[jmp]") {
    REQUIRE(jmp(0x12345678) == std::experimental::make_array<std::uint8_t>(0xE9, 0x78, 0x56, 0x34, 0x12));
    REQUIRE(jmp(rcx) == std::experimental::make_array<std::uint8_t>(0xFF, 0xE1));
    REQUIRE(jmp(ptr(rcx)) == std::experimental::make_array<std::uint8_t>(0xFF, 0x21));
}