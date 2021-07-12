#pragma once

#include "opcode_extension.hpp"
#include "operands.hpp"

namespace cx_assembler::x86 {

    enum class e_mod : std::uint8_t {
        register_indirect_addressing = 0b00,
        one_byte_signed_displacement = 0b01,
        four_byte_signed_displacement = 0b10,
        register_addressing = 0b11
    };

    template <typename Reg1, typename Reg2> requires Register<Reg1> && Register<Reg2>
    consteval std::uint8_t encode_modrm(e_mod mod, const Reg1& reg1, const Reg2& reg2) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((static_cast<std::uint8_t>(reg2.id()) & 0b111) << 3)
               + (static_cast<std::uint8_t>(reg1.id()) & 0b111);
    }

    template <typename Reg1, typename Reg2> requires Register<Reg1> && Register<Reg2>
    consteval std::uint8_t encode_modrm(const Reg1& reg1, const Reg2& reg2) {
        return encode_modrm(e_mod::register_addressing, reg1, reg2);
    }

    template <typename Reg> requires Register<Reg>
    consteval std::uint8_t encode_modrm(e_mod mod, const Reg& reg) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((static_cast<std::uint8_t>(000) & 0b111) << 3)
               + (static_cast<std::uint8_t>(reg.id()) & 0b111);
    }

    template <typename Reg> requires Register<Reg>
    consteval std::uint8_t encode_modrm(const Reg& reg) {
        return encode_modrm(e_mod::register_addressing, reg);
    }

    template <typename Mem> requires Memory<Mem> && Register<typename Mem::value_type>
    consteval std::uint8_t encode_modrm(const Mem& mem) {
        return encode_modrm(e_mod::register_indirect_addressing, mem.value());
    }

    template <typename Reg, typename Mem> requires Register<Reg> && Memory<Mem> && Register<typename Mem::value_type>
    consteval std::uint8_t encode_modrm(e_mod mod, const Reg& reg, const Mem& mem) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((static_cast<std::uint8_t>(reg.id()) & 0b111) << 3)
               + (static_cast<std::uint8_t>(mem.value().id()) & 0b111);
    }

    template <typename Reg, typename Mem> requires Register<Reg> && Memory<Mem> && Register<typename Mem::value_type>
    consteval std::uint8_t encode_modrm(const Reg& reg, const Mem& mem) {
        return encode_modrm(e_mod::register_indirect_addressing, reg, mem);
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Register<typename Mem::value_type> && Register<Reg>
    consteval std::uint8_t encode_modrm(e_mod mod, const Mem& mem, const Reg& reg) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((static_cast<std::uint8_t>(reg.id()) & 0b111) << 3)
               + (static_cast<std::uint8_t>(mem.value().id()) & 0b111);
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Register<typename Mem::value_type> && Register<Reg>
    consteval std::uint8_t encode_modrm(const Mem& mem, const Reg& reg) {
        return encode_modrm(e_mod::register_indirect_addressing, mem, reg);
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Immediate<typename Mem::value_type> && Register<Reg>
    consteval std::uint8_t encode_modrm(e_mod mod, const Mem& mem, const Reg& reg) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((static_cast<std::uint8_t>(reg.id()) & 0b111) << 3)
               + (static_cast<std::uint8_t>(0b100) & 0b111);
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Immediate<typename Mem::value_type> && Register<Reg>
    consteval std::uint8_t encode_modrm(const Mem& mem, const Reg& reg) {
        return encode_modrm(e_mod::register_indirect_addressing, mem, reg);
    }

    template <typename Reg, typename Mem> requires Register<Reg> && Memory<Mem> && Immediate<typename Mem::value_type>
    consteval std::uint8_t encode_modrm(const Reg& reg, const Mem& mem) {
        return encode_modrm(e_mod::register_indirect_addressing, mem, reg);
    }

    template <typename Reg> requires Register<Reg>
    consteval std::uint8_t encode_modrm_ext(e_mod mod, std::uint8_t ext, const Reg& reg) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((ext & 0b111) << 3)
               + (static_cast<std::uint8_t>(reg.id()) & 0b111);
    }

    template <typename Reg, typename Imm> requires Register<Reg> && Immediate<Imm>
    consteval std::uint8_t encode_modrm(e_opcode_alu_extension ext, const Reg& reg, const Imm& imm) {
        return encode_modrm_ext(e_mod::register_addressing, static_cast<std::uint8_t>(ext), reg);
    }

    template <typename Mem, typename Imm> requires Memory<Mem> && Register<typename Mem::value_type> && Immediate<Imm>
    consteval std::uint8_t encode_modrm(e_opcode_alu_extension ext, const Mem& mem, const Imm& imm) {
        return encode_modrm_ext(e_mod::register_indirect_addressing, static_cast<std::uint8_t>(ext), mem.value());
    }

    template <typename Reg, typename Imm> requires Register<Reg> && Immediate<Imm>
    consteval std::uint8_t encode_modrm(e_mod mod, e_opcode_alu_extension ext, const Reg& reg, const Imm& imm) {
        return (static_cast<std::uint8_t>(mod) << 6)
               + ((static_cast<std::uint8_t>(ext) & 0b111) << 3)
               + (static_cast<std::uint8_t>(reg.id()) & 0b111);
    }

    template <typename Reg, typename Imm> requires Register<Reg> && Immediate<Imm>
    consteval std::uint8_t encode_modrm(e_opcode_bt_extension ext, const Reg& reg, const Imm& imm) {
        return encode_modrm_ext(e_mod::register_addressing, static_cast<std::uint8_t>(ext), reg);
    }

    template <typename Reg> requires Register<Reg>
    consteval std::uint8_t encode_modrm(e_opcode_ff_extension ext, const Reg& reg) {
        return encode_modrm_ext(e_mod::register_addressing, static_cast<std::uint8_t>(ext), reg);
    }

    template <typename Mem> requires Memory<Mem>
    consteval std::uint8_t encode_modrm(e_opcode_ff_extension ext, const Mem& mem) {
        return encode_modrm_ext(e_mod::register_indirect_addressing, static_cast<std::uint8_t>(ext), mem.value());
    }
}