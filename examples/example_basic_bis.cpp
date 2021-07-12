#include "../src/cx_assembler.hpp"

#include <iostream>

using namespace cx_assembler;
using namespace cx_assembler::x86;
using namespace cx_assembler::x86::registers;
using namespace cx_assembler::x86::instructions;

int main() {

    std::cout << "this program returns 12 as well" << std::endl;

    constexpr auto code = core::assemble(
        push(rax),
        push(rcx),
        add(rsp, 8),
        mov(rcx, rsp),
        mov(qword_ptr(rcx), 12),
        sub(rsp, 8),
        pop(rcx),
        pop(rax),
        ret()
    );

    core::emit(code);
}