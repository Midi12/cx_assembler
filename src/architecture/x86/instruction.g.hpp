#pragma once

#include <cstdint>
#include <experimental/array>

#include "encoder.hpp"
#include "instruction_db.hpp"

namespace cx_assembler::x86::instructions {

    template <typename Op1, typename Op2>
    consteval auto adc(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::adc>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto add(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::add>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto and_(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::and_>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto bt(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::bt>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto btc(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::btc>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto btr(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::btr>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto bts(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::bts>(op1, op2);
    }

    template <typename Op1>
    consteval auto call(const Op1& op1) {
        return encode<e_instruction_id::call>(op1);
    }

    template <typename Op1, typename Op2>
    consteval auto cmp(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::cmp>(op1, op2);
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jb(Address address) {
        return encode<e_instruction_id::jb>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jb(Address address) {
        return jb(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jbe(Address address) {
        return encode<e_instruction_id::jbe>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jbe(Address address) {
        return jbe(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jl(Address address) {
        return encode<e_instruction_id::jl>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jl(Address address) {
        return jl(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jle(Address address) {
        return encode<e_instruction_id::jle>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jle(Address address) {
        return jle(imm8(address));
    }

    template <typename Address> requires (Immediate<Address> || Register<Address> || (Memory<Address> && Register<typename Address::value_type>))
    consteval auto jmp(Address address) {
        return encode<e_instruction_id::jmp>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jmp(Address address) {
        return jmp(imm32(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jnb(Address address) {
        return encode<e_instruction_id::jnb>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jnb(Address address) {
        return jnb(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jnbe(Address address) {
        return encode<e_instruction_id::jnbe>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jnbe(Address address) {
        return jnbe(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jnl(Address address) {
        return encode<e_instruction_id::jnl>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jnl(Address address) {
        return jnl(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jnle(Address address) {
        return encode<e_instruction_id::jnle>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jnle(Address address) {
        return jnle(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jno(Address address) {
        return encode<e_instruction_id::jno>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jno(Address address) {
        return jno(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jnp(Address address) {
        return encode<e_instruction_id::jnp>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jnp(Address address) {
        return jnp(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jns(Address address) {
        return encode<e_instruction_id::jns>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jns(Address address) {
        return jns(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jnz(Address address) {
        return encode<e_instruction_id::jnz>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jnz(Address address) {
        return jnz(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jo(Address address) {
        return encode<e_instruction_id::jo>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jo(Address address) {
        return jo(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jp(Address address) {
        return encode<e_instruction_id::jp>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jp(Address address) {
        return jp(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto js(Address address) {
        return encode<e_instruction_id::js>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto js(Address address) {
        return js(imm8(address));
    }

    template <typename Address> requires Immediate8<Address>
    consteval auto jz(Address address) {
        return encode<e_instruction_id::jz>(address);
    }

    template <typename Address> requires Integer<Address>
    consteval auto jz(Address address) {
        return jz(imm8(address));
    }


    template <typename Op1, typename Op2>
    consteval auto mov(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::mov>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto movabs(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::movabs>(op1, op2);
    }

    consteval auto nop() {
        return encode<e_instruction_id::nop>();
    }

    template <int Len>
    consteval auto nop() {
        return encode_nop<Len>();
    }

#define NOP(len) nop<len>()

    template <typename Op1, typename Op2>
    consteval auto or_(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::or_>(op1, op2);
    }

    template <typename Op1>
    consteval auto pop(const Op1& op1) {
        return encode<e_instruction_id::pop>(op1);
    }

    template <typename Op1>
    consteval auto push(const Op1& op1) {
        return encode<e_instruction_id::push>(op1);
    }

    template <typename Op1>
    consteval auto ret(const Op1& op1) {
        return encode<e_instruction_id::ret>(op1);
    }

    consteval auto ret() {
        return encode<e_instruction_id::ret>();
    }

    template <typename Op1>
    consteval auto retf(const Op1& op1) {
        return encode<e_instruction_id::retf>(op1);
    }

    consteval auto retf() {
        return encode<e_instruction_id::retf>();
    }

    template <typename Op1, typename Op2>
    consteval auto sbb(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::sbb>(op1, op2);
    }

    template <typename Op1, typename Op2>
    consteval auto sub(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::sub>(op1, op2);
    }

    consteval auto ud2() {
        return encode<e_instruction_id::ud2>();
    }

    template <typename Op1, typename Op2>
    consteval auto xor_(const Op1& op1, const Op2& op2) {
        return encode<e_instruction_id::xor_>(op1, op2);
    }

}