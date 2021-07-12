#include "../src/cx_assembler.hpp"

#include <iostream>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

int main() {

    std::cout << "this program returns 12" << std::endl;

    constexpr auto code = core::assemble(
        mov(rax, 12),
        ret()
    );

    core::emit(code);
}