#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("JCC instructions are assembled correctly", "[jcc]") {
    REQUIRE(jb(0x12) == std::experimental::make_array<std::uint8_t>(0x72, 0x12));
    REQUIRE(jbe(0x12) == std::experimental::make_array<std::uint8_t>(0x76, 0x12));
    REQUIRE(jl(0x12) == std::experimental::make_array<std::uint8_t>(0x7c, 0x12));
    REQUIRE(jle(0x12) == std::experimental::make_array<std::uint8_t>(0x7e, 0x12));
    REQUIRE(jnb(0x12) == std::experimental::make_array<std::uint8_t>(0x73, 0x12));
    REQUIRE(jnbe(0x12) == std::experimental::make_array<std::uint8_t>(0x77, 0x12));
    REQUIRE(jnl(0x12) == std::experimental::make_array<std::uint8_t>(0x7d, 0x12));
    REQUIRE(jnle(0x12) == std::experimental::make_array<std::uint8_t>(0x7f, 0x12));
    REQUIRE(jno(0x12) == std::experimental::make_array<std::uint8_t>(0x71, 0x12));
    REQUIRE(jnp(0x12) == std::experimental::make_array<std::uint8_t>(0x7b, 0x12));
    REQUIRE(jns(0x12) == std::experimental::make_array<std::uint8_t>(0x79, 0x12));
    REQUIRE(jnz(0x12) == std::experimental::make_array<std::uint8_t>(0x75, 0x12));
    REQUIRE(jo(0x12) == std::experimental::make_array<std::uint8_t>(0x70, 0x12));
    REQUIRE(jp(0x12) == std::experimental::make_array<std::uint8_t>(0x7a, 0x12));
    REQUIRE(js(0x12) == std::experimental::make_array<std::uint8_t>(0x78, 0x12));
    REQUIRE(jz(0x12) == std::experimental::make_array<std::uint8_t>(0x74, 0x12));
}