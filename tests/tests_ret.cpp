#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("RET instructions are assembled correctly", "[ret]") {
    REQUIRE(ret() == std::experimental::make_array<std::uint8_t>(0xC3));
    REQUIRE(ret(2) == std::experimental::make_array<std::uint8_t>(0xC2, 0x02, 0x00));
}

TEST_CASE("RETF instructions are assembled correctly", "[ret]") {
    REQUIRE(retf() == std::experimental::make_array<std::uint8_t>(0xCB));
    REQUIRE(retf(2) == std::experimental::make_array<std::uint8_t>(0xCA, 0x02, 0x00));
}