#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("MOV instructions are assembled correctly", "[mov]") {
    REQUIRE(mov(cl, bl) == std::experimental::make_array<std::uint8_t>(0x88, 0xD9));
    REQUIRE(mov(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x89, 0xD9));
    REQUIRE(mov(ebx, ecx) == std::experimental::make_array<std::uint8_t>(0x89, 0xCB));
    REQUIRE(mov(rbx, rcx) == std::experimental::make_array<std::uint8_t>(0x48, 0x89, 0xCB));

    REQUIRE(mov(byte_ptr(rbx), 0x12345678) == std::experimental::make_array<std::uint8_t>(0xC6, 0x03, 0x78));
    REQUIRE(mov(word_ptr(rbx), 0x12345678) == std::experimental::make_array<std::uint8_t>(0x66, 0xC7, 0x03, 0x78, 0x56));
    REQUIRE(mov(dword_ptr(rbx), 0x12345678) == std::experimental::make_array<std::uint8_t>(0xC7, 0x03, 0x78, 0x56, 0x34, 0x12));
    REQUIRE(mov(qword_ptr(rbx), 0x12345678) == std::experimental::make_array<std::uint8_t>(0x48, 0xC7, 0x03, 0x78, 0x56, 0x34, 0x12));

    REQUIRE(mov(byte_ptr(rbx), cl) == std::experimental::make_array<std::uint8_t>(0x88, 0x0B));
    REQUIRE(mov(word_ptr(rbx), cx) == std::experimental::make_array<std::uint8_t>(0x66, 0x89, 0x0B));
    REQUIRE(mov(dword_ptr(rbx), ecx) == std::experimental::make_array<std::uint8_t>(0x89, 0x0B));
    REQUIRE(mov(qword_ptr(rbx), rcx) == std::experimental::make_array<std::uint8_t>(0x48, 0x89, 0x0B));

    REQUIRE(mov(cl, 12) == std::experimental::make_array<std::uint8_t>(0xC6, 0xC1, 0x0C));
    REQUIRE(mov(cx, 12) == std::experimental::make_array<std::uint8_t>(0x66, 0xC7, 0xC1, 0x0C, 0x00));
    REQUIRE(mov(ecx, 12) == std::experimental::make_array<std::uint8_t>(0xC7, 0xC1, 0x0C, 0x00, 0x00, 0x00));
    REQUIRE(mov(rcx, 12) == std::experimental::make_array<std::uint8_t>(0x48, 0xC7, 0xC1, 0x0C, 0x00, 0x00, 0x00));

    REQUIRE(mov(r8b, 12) == std::experimental::make_array<std::uint8_t>(0x41, 0xC6, 0xC0, 0x0C));
    REQUIRE(mov(r8w, 12) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0xC7, 0xC0, 0x0C, 0x00));
    REQUIRE(mov(r8d, 12) == std::experimental::make_array<std::uint8_t>(0x41, 0xC7, 0xC0, 0x0C, 0x00, 0x00, 0x00));
    REQUIRE(mov(r8, 12) == std::experimental::make_array<std::uint8_t>(0x49, 0xC7, 0xC0, 0x0C, 0x00, 0x00, 0x00));
}

TEST_CASE("MOVABS instructions are assembled correctly", "[mov]") {
    REQUIRE(movabs(rbx, 0x1234567890ABCDEF) == std::experimental::make_array<std::uint8_t>(0x48, 0xBB, 0xEF, 0xCD, 0xAB, 0x90, 0x78, 0x56, 0x34, 0x12));
}