#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("CALL instructions are assembled correctly", "[call]") {
    REQUIRE(call(0x12345678) == std::experimental::make_array<std::uint8_t>(0xE8, 0x78, 0x56, 0x34, 0x12));
    REQUIRE(call(rcx) == std::experimental::make_array<std::uint8_t>(0xFF, 0xD1));
    REQUIRE(call(ptr(rcx)) == std::experimental::make_array<std::uint8_t>(0xFF, 0x11));
}