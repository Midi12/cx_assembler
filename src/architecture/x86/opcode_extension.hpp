#pragma once

namespace cx_assembler::x86 {

    enum class e_opcode_alu_extension {
        add =   0b000, // 0
        or_ =   0b001, // 1
        adc =   0b010, // 2
        sbb =   0b011, // 3
        and_ =  0b100, // 4
        sub =   0b101, // 5
        xor_ =  0b110, // 6
        cmp =   0b111, // 7
    };

    enum class e_opcode_bt_extension {
        bt =    0b100, // 4
        bts =   0b101, // 5
        btr =   0b110, // 6
        btc =   0b111, // 7
    };

    enum class e_opcode_ff_extension {
        call = 0b010, // 2
    };

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type"
    consteval e_opcode_alu_extension opcodeext_alu(const e_instruction_id& id) {
        switch (id) {
            case e_instruction_id::add:
                return e_opcode_alu_extension::add;
            case e_instruction_id::or_:
                return e_opcode_alu_extension::or_;
            case e_instruction_id::adc:
                return e_opcode_alu_extension::adc;
            case e_instruction_id::sbb:
                return e_opcode_alu_extension::sbb;
            case e_instruction_id::and_:
                return e_opcode_alu_extension::and_;
            case e_instruction_id::sub:
                return e_opcode_alu_extension::sub;
            case e_instruction_id::xor_:
                return e_opcode_alu_extension::xor_;
            case e_instruction_id::cmp:
                return e_opcode_alu_extension::cmp;
            default:
                static_assert("invalid instruction id");
        }
    }

    consteval e_opcode_bt_extension opcodeext_bt(const e_instruction_id& id) {
        switch (id) {
            case e_instruction_id::bt:
                return e_opcode_bt_extension::bt;
            case e_instruction_id::btc:
                return e_opcode_bt_extension::btc;
            case e_instruction_id::btr:
                return e_opcode_bt_extension::btr;
            case e_instruction_id::bts:
                return e_opcode_bt_extension::bts;
            default:
                static_assert("invalid instruction id");
        }
    }

    consteval e_opcode_ff_extension opcodeext_ff(const e_instruction_id& id) {
        switch (id) {
            case e_instruction_id::call:
                return e_opcode_ff_extension::call;
            default:
                static_assert("invalid instruction id");
        }
    }
#pragma clang diagnostic pop

}