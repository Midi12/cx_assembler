#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("BT instructions are assembled correctly", "[bt]") {
    REQUIRE(bt(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x0F,0xA3, 0xD9));
    REQUIRE(bt(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F,0xA3, 0xD9));
    REQUIRE(bt(ecx, 12) == std::experimental::make_array<std::uint8_t>(0x0F, 0xBA, 0xE1, 0x0C));
    REQUIRE(bt(rcx, 12) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F, 0xBA, 0xE1, 0x0C));
}

TEST_CASE("BTC instructions are assembled correctly", "[bt]") {
    REQUIRE(btc(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x0F,0xBB, 0xD9));
    REQUIRE(btc(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F,0xBB, 0xD9));
    REQUIRE(btc(ecx, 12) == std::experimental::make_array<std::uint8_t>(0x0F, 0xBA, 0xF9, 0x0C));
    REQUIRE(btc(rcx, 12) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F, 0xBA, 0xF9, 0x0C));
}

TEST_CASE("BTR instructions are assembled correctly", "[bt]") {
    REQUIRE(btr(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x0F,0xB3, 0xD9));
    REQUIRE(btr(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F,0xB3, 0xD9));
    REQUIRE(btr(ecx, 12) == std::experimental::make_array<std::uint8_t>(0x0F, 0xBA, 0xF1, 0x0C));
    REQUIRE(btr(rcx, 12) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F, 0xBA, 0xF1, 0x0C));
}

TEST_CASE("BTS instructions are assembled correctly", "[bt]") {
    REQUIRE(bts(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x0F,0xAB, 0xD9));
    REQUIRE(bts(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F,0xAB, 0xD9));
    REQUIRE(bts(ecx, 12) == std::experimental::make_array<std::uint8_t>(0x0F, 0xBA, 0xE9, 0x0C));
    REQUIRE(bts(rcx, 12) == std::experimental::make_array<std::uint8_t>(0x48, 0x0F, 0xBA, 0xE9, 0x0C));
}