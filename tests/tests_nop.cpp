#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("NOP instructions are assembled correctly", "[nop]") {
    REQUIRE(nop() == std::experimental::make_array<std::uint8_t>(0x90));
    REQUIRE(NOP(1) == std::experimental::make_array<std::uint8_t>(0x90));
    REQUIRE(NOP(2) == std::experimental::make_array<std::uint8_t>(0x66, 0x90));
    REQUIRE(NOP(3) == std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x00));
    REQUIRE(NOP(4) == std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x40, 0x00));
    REQUIRE(NOP(5) == std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x44, 0x00, 0x00));
    REQUIRE(NOP(6) == std::experimental::make_array<std::uint8_t>(0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00));
    REQUIRE(NOP(7) == std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00));
    REQUIRE(NOP(8) == std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00));
    REQUIRE(NOP(9) == std::experimental::make_array<std::uint8_t>(0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00));
}
