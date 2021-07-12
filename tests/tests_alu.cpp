#include "../src/cx_assembler.hpp"

#include <experimental/array>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

TEST_CASE("ADC instructions are assembled correctly", "[alu]") {
    REQUIRE(adc(cl, bl) == std::experimental::make_array<std::uint8_t>(0x10, 0xD9));
    REQUIRE(adc(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x10, 0xC8));

    REQUIRE(adc(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x11, 0xD9));
    REQUIRE(adc(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x11, 0xC8));

    REQUIRE(adc(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x11, 0xD9));
    REQUIRE(adc(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x11, 0xC8));

    REQUIRE(adc(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x11, 0xD9));
    REQUIRE(adc(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x11, 0xC8));

    REQUIRE(adc(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x11, 0xCF));

    REQUIRE(adc(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x11, 0x1F));
    REQUIRE(adc(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x11, 0x1F));

    REQUIRE(adc(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x11, 0x1F));
    REQUIRE(adc(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x11, 0x1F));

    REQUIRE(adc(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x13, 0x1F));
    REQUIRE(adc(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x13, 0x1F));

    REQUIRE(adc(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x13, 0x1F));
    REQUIRE(adc(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x13, 0x1F));

    REQUIRE(adc(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x11, 0x1F));
    REQUIRE(adc(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x11, 0x1F));
    REQUIRE(adc(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x13, 0x1F));
    REQUIRE(adc(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x13, 0x1F));

    REQUIRE(adc(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x11, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x11, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(adc(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x13, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x13, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(adc(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x11, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x13, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x12, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x12, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(adc(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xD1, 0x12));
    REQUIRE(adc(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xD1, 0x12));
    REQUIRE(adc(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xD1, 0x12, 0x12));
    REQUIRE(adc(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xD1, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xD1, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(adc(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x17, 0x12));
    REQUIRE(adc(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x17, 0x12, 0x12));
    REQUIRE(adc(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x17, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x17, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(adc(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x17, 0x12));
    REQUIRE(adc(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x17, 0x12, 0x12));
    REQUIRE(adc(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x17, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(adc(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x17, 0x12, 0x12, 0x12, 0x12));
}

TEST_CASE("ADD instructions are assembled correctly", "[alu]") {
    REQUIRE(add(cl, bl) == std::experimental::make_array<std::uint8_t>(0x00, 0xD9));
    REQUIRE(add(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x00, 0xC8));

    REQUIRE(add(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x01, 0xD9));
    REQUIRE(add(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x01, 0xC8));

    REQUIRE(add(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x01, 0xD9));
    REQUIRE(add(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x01, 0xC8));

    REQUIRE(add(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x01, 0xD9));
    REQUIRE(add(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x01, 0xC8));

    REQUIRE(add(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x01, 0xCF));

    REQUIRE(add(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x01, 0x1F));
    REQUIRE(add(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x01, 0x1F));

    REQUIRE(add(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x01, 0x1F));
    REQUIRE(add(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x01, 0x1F));

    REQUIRE(add(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x03, 0x1F));
    REQUIRE(add(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x03, 0x1F));

    REQUIRE(add(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x03, 0x1F));
    REQUIRE(add(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x03, 0x1F));

    REQUIRE(add(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x01, 0x1F));
    REQUIRE(add(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x01, 0x1F));
    REQUIRE(add(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x03, 0x1F));
    REQUIRE(add(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x03, 0x1F));

    REQUIRE(add(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x01, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x01, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(add(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x03, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x03, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(add(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x01, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x03, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x02, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x02, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(add(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xC1, 0x12));
    REQUIRE(add(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xC1, 0x12));
    REQUIRE(add(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xC1, 0x12, 0x12));
    REQUIRE(add(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xC1, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xC1, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(add(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x07, 0x12));
    REQUIRE(add(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x07, 0x12, 0x12));
    REQUIRE(add(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x07, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x07, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(add(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x07, 0x12));
    REQUIRE(add(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x07, 0x12, 0x12));
    REQUIRE(add(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x07, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(add(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x07, 0x12, 0x12, 0x12, 0x12));
}

TEST_CASE("AND instructions are assembled correctly", "[alu]") {
    REQUIRE(and_(cl, bl) == std::experimental::make_array<std::uint8_t>(0x20, 0xD9));
    REQUIRE(and_(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x20, 0xC8));

    REQUIRE(and_(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x21, 0xD9));
    REQUIRE(and_(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x21, 0xC8));

    REQUIRE(and_(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x21, 0xD9));
    REQUIRE(and_(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x21, 0xC8));

    REQUIRE(and_(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x21, 0xD9));
    REQUIRE(and_(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x21, 0xC8));

    REQUIRE(and_(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x21, 0xCF));

    REQUIRE(and_(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x21, 0x1F));
    REQUIRE(and_(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x21, 0x1F));

    REQUIRE(and_(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x21, 0x1F));
    REQUIRE(and_(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x21, 0x1F));

    REQUIRE(and_(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x23, 0x1F));
    REQUIRE(and_(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x23, 0x1F));

    REQUIRE(and_(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x23, 0x1F));
    REQUIRE(and_(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x23, 0x1F));

    REQUIRE(and_(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x21, 0x1F));
    REQUIRE(and_(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x21, 0x1F));
    REQUIRE(and_(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x23, 0x1F));
    REQUIRE(and_(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x23, 0x1F));

    REQUIRE(and_(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x21, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x21, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(and_(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x23, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x23, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(and_(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x21, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x23, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x22, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x22, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(and_(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xE1, 0x12));
    REQUIRE(and_(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xE1, 0x12));
    REQUIRE(and_(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xE1, 0x12, 0x12));
    REQUIRE(and_(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xE1, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xE1, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(and_(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x27, 0x12));
    REQUIRE(and_(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x27, 0x12, 0x12));
    REQUIRE(and_(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x27, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x27, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(and_(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x27, 0x12));
    REQUIRE(and_(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x27, 0x12, 0x12));
    REQUIRE(and_(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x27, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(and_(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x27, 0x12, 0x12, 0x12, 0x12));
}

TEST_CASE("CMP instructions are assembled correctly", "[alu]") {
    REQUIRE(cmp(cl, bl) == std::experimental::make_array<std::uint8_t>(0x38, 0xD9));
    REQUIRE(cmp(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x38, 0xC8));

    REQUIRE(cmp(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x39, 0xD9));
    REQUIRE(cmp(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x39, 0xC8));

    REQUIRE(cmp(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x39, 0xD9));
    REQUIRE(cmp(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x39, 0xC8));

    REQUIRE(cmp(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x39, 0xD9));
    REQUIRE(cmp(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x39, 0xC8));

    REQUIRE(cmp(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x39, 0xCF));

    REQUIRE(cmp(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x39, 0x1F));
    REQUIRE(cmp(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x39, 0x1F));

    REQUIRE(cmp(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x39, 0x1F));
    REQUIRE(cmp(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x39, 0x1F));

    REQUIRE(cmp(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x3B, 0x1F));
    REQUIRE(cmp(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x3B, 0x1F));

    REQUIRE(cmp(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x3B, 0x1F));
    REQUIRE(cmp(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x3B, 0x1F));

    REQUIRE(cmp(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x39, 0x1F));
    REQUIRE(cmp(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x39, 0x1F));
    REQUIRE(cmp(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x3B, 0x1F));
    REQUIRE(cmp(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x3B, 0x1F));

    REQUIRE(cmp(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x39, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x39, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(cmp(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x3B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x3B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(cmp(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x39, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x3B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x3A, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x3A, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(cmp(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xF9, 0x12));
    REQUIRE(cmp(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xF9, 0x12));
    REQUIRE(cmp(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xF9, 0x12, 0x12));
    REQUIRE(cmp(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xF9, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xF9, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(cmp(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x3F, 0x12));
    REQUIRE(cmp(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x3F, 0x12, 0x12));
    REQUIRE(cmp(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x3F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x3F, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(cmp(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x3F, 0x12));
    REQUIRE(cmp(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x3F, 0x12, 0x12));
    REQUIRE(cmp(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x3F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(cmp(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x3F, 0x12, 0x12, 0x12, 0x12));
}
TEST_CASE("OR instructions are assembled correctly", "[alu]") {
    REQUIRE(or_(cl, bl) == std::experimental::make_array<std::uint8_t>(0x08, 0xD9));
    REQUIRE(or_(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x08, 0xC8));

    REQUIRE(or_(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x09, 0xD9));
    REQUIRE(or_(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x09, 0xC8));

    REQUIRE(or_(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x09, 0xD9));
    REQUIRE(or_(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x09, 0xC8));

    REQUIRE(or_(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x09, 0xD9));
    REQUIRE(or_(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x09, 0xC8));

    REQUIRE(or_(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x09, 0xCF));

    REQUIRE(or_(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x09, 0x1F));
    REQUIRE(or_(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x09, 0x1F));

    REQUIRE(or_(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x09, 0x1F));
    REQUIRE(or_(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x09, 0x1F));

    REQUIRE(or_(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x0B, 0x1F));
    REQUIRE(or_(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x0B, 0x1F));

    REQUIRE(or_(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x0B, 0x1F));
    REQUIRE(or_(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x0B, 0x1F));

    REQUIRE(or_(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x09, 0x1F));
    REQUIRE(or_(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x09, 0x1F));
    REQUIRE(or_(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x0B, 0x1F));
    REQUIRE(or_(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x0B, 0x1F));

    REQUIRE(or_(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x09, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x09, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(or_(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x0B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x0B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(or_(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x09, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x0B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x0A, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x0A, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(or_(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xC9, 0x12));
    REQUIRE(or_(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xC9, 0x12));
    REQUIRE(or_(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xC9, 0x12, 0x12));
    REQUIRE(or_(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xC9, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xC9, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(or_(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x0F, 0x12));
    REQUIRE(or_(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x0F, 0x12, 0x12));
    REQUIRE(or_(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x0F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x0F, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(or_(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x0F, 0x12));
    REQUIRE(or_(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x0F, 0x12, 0x12));
    REQUIRE(or_(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x0F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(or_(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x0F, 0x12, 0x12, 0x12, 0x12));
}

TEST_CASE("SBB instructions are assembled correctly", "[alu]") {
    REQUIRE(sbb(cl, bl) == std::experimental::make_array<std::uint8_t>(0x18, 0xD9));
    REQUIRE(sbb(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x18, 0xC8));

    REQUIRE(sbb(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x19, 0xD9));
    REQUIRE(sbb(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x19, 0xC8));

    REQUIRE(sbb(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x19, 0xD9));
    REQUIRE(sbb(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x19, 0xC8));

    REQUIRE(sbb(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x19, 0xD9));
    REQUIRE(sbb(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x19, 0xC8));

    REQUIRE(sbb(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x19, 0xCF));

    REQUIRE(sbb(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x19, 0x1F));
    REQUIRE(sbb(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x19, 0x1F));

    REQUIRE(sbb(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x19, 0x1F));
    REQUIRE(sbb(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x19, 0x1F));

    REQUIRE(sbb(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x1B, 0x1F));
    REQUIRE(sbb(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x1B, 0x1F));

    REQUIRE(sbb(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x1B, 0x1F));
    REQUIRE(sbb(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x1B, 0x1F));

    REQUIRE(sbb(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x19, 0x1F));
    REQUIRE(sbb(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x19, 0x1F));
    REQUIRE(sbb(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x1B, 0x1F));
    REQUIRE(sbb(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x1B, 0x1F));

    REQUIRE(sbb(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x19, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x19, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sbb(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x1B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x1B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sbb(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x19, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x1B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x1A, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x1A, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sbb(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xD9, 0x12));
    REQUIRE(sbb(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xD9, 0x12));
    REQUIRE(sbb(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xD9, 0x12, 0x12));
    REQUIRE(sbb(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xD9, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xD9, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sbb(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x1F, 0x12));
    REQUIRE(sbb(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x1F, 0x12, 0x12));
    REQUIRE(sbb(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x1F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x1F, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sbb(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x1F, 0x12));
    REQUIRE(sbb(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x1F, 0x12, 0x12));
    REQUIRE(sbb(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x1F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sbb(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x1F, 0x12, 0x12, 0x12, 0x12));
}

TEST_CASE("SUB instructions are assembled correctly", "[alu]") {
    REQUIRE(sub(cl, bl) == std::experimental::make_array<std::uint8_t>(0x28, 0xD9));
    REQUIRE(sub(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x28, 0xC8));

    REQUIRE(sub(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x29, 0xD9));
    REQUIRE(sub(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x29, 0xC8));

    REQUIRE(sub(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x29, 0xD9));
    REQUIRE(sub(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x29, 0xC8));

    REQUIRE(sub(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x29, 0xD9));
    REQUIRE(sub(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x29, 0xC8));

    REQUIRE(sub(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x29, 0xCF));

    REQUIRE(sub(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x29, 0x1F));
    REQUIRE(sub(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x29, 0x1F));

    REQUIRE(sub(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x29, 0x1F));
    REQUIRE(sub(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x29, 0x1F));

    REQUIRE(sub(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x2B, 0x1F));
    REQUIRE(sub(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x2B, 0x1F));

    REQUIRE(sub(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x2B, 0x1F));
    REQUIRE(sub(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x2B, 0x1F));

    REQUIRE(sub(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x29, 0x1F));
    REQUIRE(sub(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x29, 0x1F));
    REQUIRE(sub(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x2B, 0x1F));
    REQUIRE(sub(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x2B, 0x1F));

    REQUIRE(sub(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x29, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x29, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sub(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x2B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x2B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sub(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x29, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x2B, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x2A, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x2A, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sub(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xE9, 0x12));
    REQUIRE(sub(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xE9, 0x12));
    REQUIRE(sub(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xE9, 0x12, 0x12));
    REQUIRE(sub(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xE9, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xE9, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sub(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x2F, 0x12));
    REQUIRE(sub(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x2F, 0x12, 0x12));
    REQUIRE(sub(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x2F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x2F, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(sub(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x2F, 0x12));
    REQUIRE(sub(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x2F, 0x12, 0x12));
    REQUIRE(sub(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x2F, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(sub(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x2F, 0x12, 0x12, 0x12, 0x12));
}

TEST_CASE("XOR instructions are assembled correctly", "[alu]") {
    REQUIRE(xor_(cl, bl) == std::experimental::make_array<std::uint8_t>(0x30, 0xD9));
    REQUIRE(xor_(r8b, r9b) == std::experimental::make_array<std::uint8_t>(0x45, 0x30, 0xC8));

    REQUIRE(xor_(cx, bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x31, 0xD9));
    REQUIRE(xor_(r8w, r9w) == std::experimental::make_array<std::uint8_t>(0x66, 0x45, 0x31, 0xC8));

    REQUIRE(xor_(ecx, ebx) == std::experimental::make_array<std::uint8_t>(0x31, 0xD9));
    REQUIRE(xor_(r8d, r9d) == std::experimental::make_array<std::uint8_t>(0x45, 0x31, 0xC8));

    REQUIRE(xor_(rcx, rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x31, 0xD9));
    REQUIRE(xor_(r8, r9) == std::experimental::make_array<std::uint8_t>(0x4D, 0x31, 0xC8));

    REQUIRE(xor_(rdi, r9) == std::experimental::make_array<std::uint8_t>(0x4C, 0x31, 0xCF));

    REQUIRE(xor_(ptr(edi), ebx) == std::experimental::make_array<std::uint8_t>(0x67, 0x31, 0x1F));
    REQUIRE(xor_(ptr(edi), rbx) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x31, 0x1F));

    REQUIRE(xor_(ptr(rdi), ebx) == std::experimental::make_array<std::uint8_t>(0x31, 0x1F));
    REQUIRE(xor_(ptr(rdi), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x31, 0x1F));

    REQUIRE(xor_(ebx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x33, 0x1F));
    REQUIRE(xor_(rbx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x33, 0x1F));

    REQUIRE(xor_(ebx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x33, 0x1F));
    REQUIRE(xor_(rbx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x48, 0x33, 0x1F));

    REQUIRE(xor_(ptr(edi), bx) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x31, 0x1F));
    REQUIRE(xor_(ptr(rdi), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x31, 0x1F));
    REQUIRE(xor_(bx, ptr(edi)) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x33, 0x1F));
    REQUIRE(xor_(bx, ptr(rdi)) == std::experimental::make_array<std::uint8_t>(0x66, 0x33, 0x1F));

    REQUIRE(xor_(dword_ptr(0x12121212), ebx) == std::experimental::make_array<std::uint8_t>(0x31, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(qword_ptr(0x12121212), rbx) == std::experimental::make_array<std::uint8_t>(0x48, 0x31, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(xor_(ebx, dword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x33, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(rbx, qword_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x48, 0x33, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(xor_(word_ptr(0x12121212), bx) == std::experimental::make_array<std::uint8_t>(0x66, 0x31, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(bx, word_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x66, 0x33, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(bl, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x32, 0x1C, 0x25, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(r8b, byte_ptr(0x12121212)) == std::experimental::make_array<std::uint8_t>(0x44, 0x32, 0x04, 0x25, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(xor_(cl, 0x12) == std::experimental::make_array<std::uint8_t>(0x80, 0xF1, 0x12));
    REQUIRE(xor_(r9b, 0x12) == std::experimental::make_array<std::uint8_t>(0x41, 0x80, 0xF1, 0x12));
    REQUIRE(xor_(r9w, 0x1212) == std::experimental::make_array<std::uint8_t>(0x66, 0x41, 0x81, 0xF1, 0x12, 0x12));
    REQUIRE(xor_(r9d, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x41, 0x81, 0xF1, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(r9, 0x12121212) == std::experimental::make_array<std::uint8_t>(0x49, 0x81, 0xF1, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(xor_(byte_ptr(edi), 0x12) == std::experimental::make_array<std::uint8_t>(0x67, 0x80, 0x37, 0x12));
    REQUIRE(xor_(word_ptr(edi), 0x1212) == std::experimental::make_array<std::uint8_t>(0x67, 0x66, 0x81, 0x37, 0x12, 0x12));
    REQUIRE(xor_(dword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x81, 0x37, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(qword_ptr(edi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x67, 0x48, 0x81, 0x37, 0x12, 0x12, 0x12, 0x12));

    REQUIRE(xor_(byte_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x80, 0x37, 0x12));
    REQUIRE(xor_(word_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x66, 0x81, 0x37, 0x12, 0x12));
    REQUIRE(xor_(dword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x81, 0x37, 0x12, 0x12, 0x12, 0x12));
    REQUIRE(xor_(qword_ptr(rdi), 0x12121212) == std::experimental::make_array<std::uint8_t>(0x48, 0x81, 0x37, 0x12, 0x12, 0x12, 0x12));
}
