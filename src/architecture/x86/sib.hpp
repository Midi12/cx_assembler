#pragma once

namespace cx_assembler::x86 {

    template <typename Op1, typename Op2>
    consteval std::uint8_t encode_sib_nodisp(const Op1& op1, const Op2& op2) {
        return (static_cast<std::uint8_t>(0b00) << 6) // Scale
               + ((static_cast<std::uint8_t>(0b100) & 0b111) << 3) // index
               + (static_cast<std::uint8_t>(0b101) & 0b111); // base
    }

}