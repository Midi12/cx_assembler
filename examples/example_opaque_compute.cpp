#include "../src/cx_assembler.hpp"

#include <iostream>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

int main() {

    std::cout << "this program still returns 12" << std::endl;

    constexpr auto code = core::assemble(
        xor_(eax, eax),
        mov(eax, 0x0C),
        add(eax, 0xff),
        adc(eax, 0x01),
        ret()
    );

    core::emit(code);
}