#pragma once

#include <experimental/array>

namespace cx_assembler::x86 {

    enum class e_instruction_id {
        unknown,
        adc,
        add,
        and_,
        bt,
        btc,
        btr,
        bts,
        call,
        cmp,
        mov,
        movabs,
        nop,
        or_,
        pop,
        push,
        ret,
        retf,
        sbb,
        sub,
        ud2,
        xor_,

        //----
        count
    };

    // Encoding hint
    enum class e_encoding {
        alu,
        bt,
        call,
        mov,
        pop,
        push,
        ret,
        noops
    };

    // Register/ Opcode Field
    enum class e_regopc_field {
        none,
        opcode_ext, // opcode_ext indicates the value of the opcode extension to be assigned to the ModR/M reg bits (values from 0 through 7).
        regrm // regrm indicates that the ModR/M byte contains a register operand and an r/m operand.
    };

    class instruction_desc {
    public:
        consteval instruction_desc(
                e_instruction_id id,
                std::uint8_t prefix,
                std::uint8_t prefix_0f,
                std::uint8_t primary_opcode,
                std::uint8_t secondary_opcode,
                e_encoding encoding,
                e_regopc_field regopc_field
        ) :
                _id(id),
                _prefix(prefix),
                _prefix_0f(prefix_0f),
                _primary_opcode(primary_opcode),
                _secondary_opcode(secondary_opcode),
                _encoding(encoding),
                _regopc_field(regopc_field)
        {}

        constexpr e_instruction_id id() const { return _id; }
        constexpr std::uint8_t prefix() const { return _prefix; }
        constexpr std::uint8_t prefix_0f() const { return _prefix_0f; }
        constexpr std::uint8_t primary_opcode() const { return _primary_opcode; }
        constexpr std::uint8_t secondary_opcode() const { return _secondary_opcode; }
        constexpr e_encoding encoding() const { return _encoding; }
        constexpr e_regopc_field regopc_field() const { return _regopc_field; }

    private:
        e_instruction_id _id;
        std::uint8_t _prefix;
        std::uint8_t _prefix_0f;
        std::uint8_t _primary_opcode;
        std::uint8_t _secondary_opcode;
        e_encoding _encoding;
        e_regopc_field _regopc_field;
    };

    // ud2 instruction description
    constexpr instruction_desc _ud2(e_instruction_id::unknown, 0x0, 0x0f, 0x0b, 0x0, e_encoding::noops, e_regopc_field::none);

    using instructiondb = std::array<instruction_desc, static_cast<int>(e_instruction_id::count) - 1>;
}