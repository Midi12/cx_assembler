#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("POP instructions are assembled correctly", "[pop]") {
    REQUIRE(pop(rcx) == std::experimental::make_array<std::uint8_t>(0x59));
}