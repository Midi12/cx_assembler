#pragma once

namespace cx_assembler::x86 {

    template <typename Reg1, typename Reg2> requires Register<Reg1> && Register<Reg2>
    consteval std::uint8_t encode_rex() {
        return (0b0100 << 4) // fixed value
               + ((Reg1::size >= 64 || Reg2::size >= 64) << 3) // Rex.W
               + ((Reg2::extended ? 1 : 0) << 2) // Rex.R
               + (0 << 1) // Rex.X
               + (Reg1::extended ? 1 : 0); // Rex.B
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Register<typename Mem::value_type> && Register<Reg>
    consteval std::uint8_t encode_rex() {
        return encode_rex<typename Mem::value_type, Reg>();
    }

    template <typename Reg, typename Mem> requires Register<Reg> && Memory<Mem> && Register<typename Mem::value_type>
    consteval std::uint8_t encode_rex() {
        return encode_rex<Reg, typename Mem::value_type>();
    }

    template <typename Reg1> requires Register<Reg1>
    consteval std::uint8_t encode_rex() {
        return (0b0100 << 4) // fixed value
               + ((Reg1::size >= 64) << 3) // Rex.W
               + (0 << 2) // Rex.R
               + (0 << 1) // Rex.X
               + (Reg1::extended ? 1 : 0); // Rex.B
    }

    template <typename Mem> requires Memory<Mem>
    consteval std::uint8_t encode_rex() {
        return (0b0100 << 4) // fixed value
               + ((Mem::size >= 64) << 3) // Rex.W
               + (0 << 2) // Rex.R
               + (0 << 1) // Rex.X
               + (0); // Rex.B
    }

    template <typename Imm> requires Immediate<Imm>
    consteval std::uint8_t encode_rex() {
        return 0; // todo
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Immediate<typename Mem::value_type> && Register<Reg>
    consteval std::uint8_t encode_rex() {
        return (0b0100 << 4) // fixed value
               + ((Reg::size >= 64) << 3) // Rex.W
               + (0 << 2) // Rex.R
               + (0 << 1) // Rex.X
               + (Reg::extended ? 1 : 0); // Rex.B
    }

    template <typename Reg, typename Mem> requires Register<Reg> && Memory<Mem> && Immediate<typename Mem::value_type>
    consteval std::uint8_t encode_rex() {
        return (0b0100 << 4) // fixed value
               + ((Reg::size >= 64) << 3) // Rex.W
               + ((Reg::extended ? 1 : 0) << 2) // Rex.R
               + (0 << 1) // Rex.X
               + (0); // Rex.B
    }

    template <typename Reg1, typename Reg2> requires Register<Reg1> && Register<Reg2>
    consteval bool needs_rex() {
        return Reg1::extended || Reg2::extended || Reg1::size >= 64 || Reg2::size >= 64;
    }

    template <typename Reg1> requires Register<Reg1>
    consteval bool needs_rex() {
        return Reg1::extended || Reg1::size >= 64;
    }

    template <typename Mem> requires Memory<Mem> && Register<typename Mem::value_type>
    consteval bool needs_rex() {
        return Mem::size >= 64;
    }

    template <typename Imm> requires Immediate<Imm>
    consteval bool needs_rex() {
        return sizeof(Imm) >= 64;
    }

    template <typename Mem, typename Reg> requires Memory<Mem> && Register<Reg>
    consteval bool needs_rex() {
        return Reg::extended || Reg::size >= 64;
    }

    template <typename Reg, typename Mem> requires Register<Reg> && Memory<Mem>
    consteval bool needs_rex() {
        return needs_rex<Mem, Reg>();
    }

}