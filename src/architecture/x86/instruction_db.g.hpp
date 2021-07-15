#pragma once

#include <experimental/array>

#include "instruction_db.hpp"

namespace cx_assembler::x86 {

#define INST_ENTRY(inst_id, prefix, prefix_0f, pri_opcode, sec_opcode, encoding, x) \
    instruction_desc(e_instruction_id::inst_id, prefix, prefix_0f, pri_opcode, sec_opcode, e_encoding::encoding, e_regopc_field::x)

    constexpr instructiondb instdb = std::experimental::make_array<instructiondb::value_type>(
            INST_ENTRY(adc, 0, 0, 0x10, 0, alu, regrm),
            INST_ENTRY(add, 0, 0, 0x00, 0, alu, regrm),
            INST_ENTRY(and_, 0, 0, 0x20, 0, alu, regrm),
            INST_ENTRY(bt, 0, 0x0f, 0xa3, 0, bt, regrm),
            INST_ENTRY(btc, 0, 0x0f, 0xba, 0, bt, regrm),
            INST_ENTRY(btr, 0, 0x0f, 0xb3, 0, bt, regrm),
            INST_ENTRY(bts, 0, 0x0f, 0xab, 0, bt, regrm),
            INST_ENTRY(call, 0, 0, 0xFF, 0, call, regrm),
            INST_ENTRY(cmp, 0, 0, 0x38, 0, alu, regrm),
            INST_ENTRY(jb, 0, 0, 0x72, 0, jcc, regrm),
            INST_ENTRY(jbe, 0, 0, 0x76, 0, jcc, regrm),
            INST_ENTRY(jl, 0, 0, 0x7c, 0, jcc, regrm),
            INST_ENTRY(jle, 0, 0, 0x7e, 0, jcc, regrm),
            INST_ENTRY(jmp, 0, 0, 0xe9, 0, jmp, regrm),
            INST_ENTRY(jnb, 0, 0, 0x73, 0, jcc, regrm),
            INST_ENTRY(jnbe, 0, 0, 0x77, 0, jcc, regrm),
            INST_ENTRY(jnl, 0, 0, 0x7d, 0, jcc, regrm),
            INST_ENTRY(jnle, 0, 0, 0x7f, 0, jcc, regrm),
            INST_ENTRY(jno, 0, 0, 0x71, 0, jcc, regrm),
            INST_ENTRY(jnp, 0, 0, 0x7b, 0, jcc, regrm),
            INST_ENTRY(jns, 0, 0, 0x79, 0, jcc, regrm),
            INST_ENTRY(jnz, 0, 0, 0x75, 0, jcc, regrm),
            INST_ENTRY(jo, 0, 0, 0x70, 0, jcc, regrm),
            INST_ENTRY(jp, 0, 0, 0x7A, 0, jcc, regrm),
            INST_ENTRY(js, 0, 0, 0x78, 0, jcc, regrm),
            INST_ENTRY(jz, 0, 0, 0x74, 0, jcc, regrm),
            INST_ENTRY(mov, 0, 0, 0x88, 0, mov, regrm),
            INST_ENTRY(movabs, 0, 0, 0xbb, 0, mov, regrm),
            INST_ENTRY(nop, 0, 0, 0x90, 0, noops, regrm),
            INST_ENTRY(or_, 0, 0, 0x08, 0, alu, regrm),
            INST_ENTRY(pop, 0, 0, 0x58, 0, pop, regrm),
            INST_ENTRY(push, 0, 0, 0x50, 0, push, regrm),
            INST_ENTRY(ret, 0, 0, 0xc3, 0, ret, none),
            INST_ENTRY(retf, 0, 0, 0xcb, 0, ret, none),
            INST_ENTRY(sbb, 0, 0, 0x18, 0, alu, regrm),
            INST_ENTRY(sub, 0, 0, 0x28, 0, alu, regrm),
            INST_ENTRY(ud2, 0, 0x0f, 0x0b, 0, noops, none),
            INST_ENTRY(xor_, 0, 0, 0x30, 0, alu, regrm)
    );

    template <e_instruction_id Id>
    consteval instruction_desc find_instruction_desc() {
        constexpr int iid = static_cast<int>(Id) - 1;
        return (iid >= 0 && iid < instdb.size()) ? instdb[iid] : _ud2;
    }

#define HAS_PREFIX_ENTRY(inst_id, has_prefix) \
    has_prefix

    constexpr auto prefix_db = std::experimental::make_array<bool>(
            HAS_PREFIX_ENTRY(adc, false),
            HAS_PREFIX_ENTRY(add, false),
            HAS_PREFIX_ENTRY(and_, false),
            HAS_PREFIX_ENTRY(bt, false),
            HAS_PREFIX_ENTRY(btc, false),
            HAS_PREFIX_ENTRY(btr, false),
            HAS_PREFIX_ENTRY(bts, false),
            HAS_PREFIX_ENTRY(call, false),
            HAS_PREFIX_ENTRY(jb, false),
            HAS_PREFIX_ENTRY(jbe, false),
            HAS_PREFIX_ENTRY(jl, false),
            HAS_PREFIX_ENTRY(jle, false),
            HAS_PREFIX_ENTRY(jmp, false),
            HAS_PREFIX_ENTRY(jnb, false),
            HAS_PREFIX_ENTRY(jnbe, false),
            HAS_PREFIX_ENTRY(jnl, false),
            HAS_PREFIX_ENTRY(jnle, false),
            HAS_PREFIX_ENTRY(jno, false),
            HAS_PREFIX_ENTRY(jnp, false),
            HAS_PREFIX_ENTRY(jns, false),
            HAS_PREFIX_ENTRY(jnz, false),
            HAS_PREFIX_ENTRY(jo, false),
            HAS_PREFIX_ENTRY(jp, false),
            HAS_PREFIX_ENTRY(js, false),
            HAS_PREFIX_ENTRY(jz, false),
            HAS_PREFIX_ENTRY(cmp, false),
            HAS_PREFIX_ENTRY(mov, false),
            HAS_PREFIX_ENTRY(movabs, false),
            HAS_PREFIX_ENTRY(or_, false),
            HAS_PREFIX_ENTRY(pop, false),
            HAS_PREFIX_ENTRY(push, false),
            HAS_PREFIX_ENTRY(ret, false),
            HAS_PREFIX_ENTRY(retf, false),
            HAS_PREFIX_ENTRY(sbb, false),
            HAS_PREFIX_ENTRY(sub, false),
            HAS_PREFIX_ENTRY(ud2, false),
            HAS_PREFIX_ENTRY(xor_, false)
    );

    template <e_instruction_id Id>
    consteval bool has_prefix() {
        constexpr int iid = static_cast<int>(Id) - 1;
        return (iid >= 0 && iid < prefix_db.size()) ? prefix_db[iid] : false;
    }

#define HAS_PREFIX_0F_ENTRY(inst_id, has_prefix_0f) \
    has_prefix_0f

    constexpr auto prefix_0fdb = std::experimental::make_array<bool>(
            HAS_PREFIX_0F_ENTRY(adc, false),
            HAS_PREFIX_0F_ENTRY(add, false),
            HAS_PREFIX_0F_ENTRY(and_, false),
            HAS_PREFIX_0F_ENTRY(bt, true),
            HAS_PREFIX_0F_ENTRY(btc, true),
            HAS_PREFIX_0F_ENTRY(btr, true),
            HAS_PREFIX_0F_ENTRY(bts, true),
            HAS_PREFIX_0F_ENTRY(call, false),
            HAS_PREFIX_0F_ENTRY(jb, false),
            HAS_PREFIX_0F_ENTRY(jbe, false),
            HAS_PREFIX_0F_ENTRY(jl, false),
            HAS_PREFIX_0F_ENTRY(jle, false),
            HAS_PREFIX_0F_ENTRY(jmp, false),
            HAS_PREFIX_0F_ENTRY(jnb, false),
            HAS_PREFIX_0F_ENTRY(jnbe, false),
            HAS_PREFIX_0F_ENTRY(jnl, false),
            HAS_PREFIX_0F_ENTRY(jnle, false),
            HAS_PREFIX_0F_ENTRY(jno, false),
            HAS_PREFIX_0F_ENTRY(jnp, false),
            HAS_PREFIX_0F_ENTRY(jns, false),
            HAS_PREFIX_0F_ENTRY(jnz, false),
            HAS_PREFIX_0F_ENTRY(jo, false),
            HAS_PREFIX_0F_ENTRY(jp, false),
            HAS_PREFIX_0F_ENTRY(js, false),
            HAS_PREFIX_0F_ENTRY(jz, false),
            HAS_PREFIX_0F_ENTRY(cmp, false),
            HAS_PREFIX_0F_ENTRY(mov, false),
            HAS_PREFIX_0F_ENTRY(movabs, false),
            HAS_PREFIX_0F_ENTRY(or_, false),
            HAS_PREFIX_0F_ENTRY(pop, false),
            HAS_PREFIX_0F_ENTRY(push, false),
            HAS_PREFIX_0F_ENTRY(ret, false),
            HAS_PREFIX_0F_ENTRY(retf, false),
            HAS_PREFIX_0F_ENTRY(sbb, false),
            HAS_PREFIX_0F_ENTRY(sub, false),
            HAS_PREFIX_0F_ENTRY(ud2, false),
            HAS_PREFIX_0F_ENTRY(xor_, false)
    );

    template <e_instruction_id Id>
    consteval bool has_prefix_0f() {
        constexpr int iid = static_cast<int>(Id) - 1;
        return (iid >= 0 && iid < prefix_0fdb.size()) ? prefix_0fdb[iid] : false;
    }

}