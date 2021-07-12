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