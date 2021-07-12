#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("PUSH instructions are assembled correctly", "[push]") {
    REQUIRE(push(rcx) == std::experimental::make_array<std::uint8_t>(0x51));
    REQUIRE(push(rbx) == std::experimental::make_array<std::uint8_t>(0x53));

    REQUIRE(push(imm8(0x12)) == std::experimental::make_array<std::uint8_t>(0x6A, 0x12));
    REQUIRE(push(0x1234) == std::experimental::make_array<std::uint8_t>(0x68, 0x34, 0x12, 0x00, 0x00));
    REQUIRE(push(0x12345678) == std::experimental::make_array<std::uint8_t>(0x68, 0x78, 0x56, 0x34, 0x12));
}