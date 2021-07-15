#pragma once

#include <experimental/array>
#include <tuple>
#include <utility>

#include "instruction_db.hpp"
#include "instruction_db.g.hpp"
#include "opcode_extension.hpp"
#include "operands.hpp"
#include "rex.hpp"

namespace cx_assembler::x86 {

    namespace internal {

        constexpr std::uint8_t prefix_16bit = 0x66;
        constexpr std::uint8_t prefix_overridesize = 0x67;

        template <typename... Ts>
        struct _sizeof {
            constexpr static std::size_t value = (sizeof(Ts) + ...);
        };

        template <typename... Ts>
        inline constexpr auto _sizeof_v = _sizeof<Ts...>::value;

        template <e_instruction_id Id, typename Op1, typename Op2>
        struct _sizeof_prefixes {
            constexpr static std::size_t value =
                    has_prefix<Id>() +
                    has_prefix_0f<Id>() +
                    ((Register16<Op1> || (!IsVoidOperand<Op2> && Register16<Op2>)) || (Memory<Op1> && Op1::size == 16) ? 1 : 0) +
                    ((Memory<Op1> && Register32<typename Op1::value_type>) || (!IsVoidOperand<Op2> && Memory<Op2> && Register32<typename Op2::value_type>) ? 1 : 0);
        };

        template <e_instruction_id Id, typename Op1, typename Op2>
        inline constexpr auto _sizeof_prefixes_v = _sizeof_prefixes<Id, Op1, Op2>::value;

        template<typename... Bytes>
        constexpr std::array<std::uint8_t, sizeof...(Bytes)> make_bytes(Bytes&&... args) noexcept {
            return { std::uint8_t(std::forward<Bytes>(args))... };
        }

        template <e_instruction_id Id, typename Op1, typename Op2, typename ...Args> requires DerivesBaseOperand<Op1> && (DerivesBaseOperand<Op2> || IsVoidOperand<Op2>)
        constexpr auto encode(instruction_desc desc, Args&& ...args) {
            auto tuple = std::make_tuple(std::forward<Args>(args)...);

            auto has_rex = []() constexpr {
                if constexpr (Immediate<Op2> || IsVoidOperand<Op2>) {
                    return (Id != e_instruction_id::call &&
                            Id != e_instruction_id::jmp
                    ) && needs_rex<Op1>();
                } else {
                    return needs_rex<Op1, Op2>();
                }
            };

            constexpr auto size = has_rex() + _sizeof_prefixes_v<Id, Op1, Op2> + _sizeof_v<Args...>;
            std::array<std::uint8_t, size> arr {};

            int j = 0;

            if constexpr ((Memory<Op1> && Register32<typename Op1::value_type>) || (!IsVoidOperand<Op2> && Memory<Op2> && Register32<typename Op2::value_type>)) {
                arr[j++] = prefix_overridesize;
            }

            if constexpr ((Register16<Op1> || (!IsVoidOperand<Op2> && Register16<Op2>)) || (Memory<Op1> && Op1::size == 16)) {
                arr[j++] = prefix_16bit;
            }

            if constexpr (has_rex()) {
                if constexpr (Immediate<Op2> || IsVoidOperand<Op2>) {
                    arr[j++] = encode_rex<Op1>();
                } else {
                    arr[j++] = encode_rex<Op1, Op2>();
                }
            }

            if constexpr (has_prefix<Id>()) {
                arr[j++] = desc.prefix();
            }

            if constexpr (has_prefix_0f<Id>()) {
                arr[j++] = desc.prefix_0f();
            }

            auto emit = [] <typename T> (std::array<std::uint8_t, size>& arr, int& j, const T& value) {
                for (int i = 0; i < sizeof(T); i++) {
                    arr[j++] = static_cast<std::uint8_t>(value >> (i * 8));
                }
            };

            std::apply([&arr, &j, &emit](auto&&... args) {
                ((emit(arr, j, args)), ...);
            }, tuple);

            return arr;
        }
    }

    template <typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Register<Op2> || Memory<Op2>)
    consteval auto encode_opcode_alu(const std::uint8_t& opcode) {
        return static_cast<std::uint8_t>(
                (opcode & 0b11111100) +
                (Memory<Op2> ? 0b10 : 0b00) + // setup bit `d`
                (Op1::size > 8 ? 0b01 : 0b00)// setup bit `s`
        );
    }

    template <typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Immediate<Op2>)
    consteval auto encode_opcode_alu(const std::uint8_t& opcode) {
        return static_cast<std::uint8_t>(
                (opcode & 0b11111100) +
                (false ? 0b10 : 0b00) + // setup bit `x` : todo : change to handle onebyte sign extend (1), constant same size as operand (0)
                (Op2::size > 8 ? 0b01 : 0b00)// setup bit `s`
        );
    }

    template <typename Reg> requires Register<Reg>
    consteval auto encode_opcode_pushpop(const std::uint8_t& opcode, const Reg& reg) {
        return static_cast<std::uint8_t>(opcode + static_cast<std::uint8_t>(reg.id()));
    }

    template <e_instruction_id Id, typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Register<Op2> || Memory<Op2> || Immediate<Op2>)
    consteval auto encode_alu(instruction_desc desc, Op1 op1, Op2 op2) {
        auto id = desc.id();
        auto opcode = desc.primary_opcode();

        if constexpr (Immediate<Op2>) {
            // Immediate src operands use the 80h opcode
            opcode = encode_opcode_alu<Op1, Op2>(0x80);
            typename Op2::value_type value = static_cast<typename Op2::value_type>(op2.value());

            return internal::encode<Id, Op1, Op2>(desc, opcode, encode_modrm(opcodeext_alu(id), op1, op2), value);
        } else {
            // src operand is Register or Memory
            opcode = encode_opcode_alu<Op1, Op2>(opcode);

            if constexpr (Memory<Op1> && Immediate<typename Op1::value_type>) {
                return internal::encode<Id, Op1, Op2>(
                        desc,
                        opcode,
                        encode_modrm(op1, op2),
                        encode_sib_nodisp(op1, op2),
                        static_cast<std::uint32_t>(op1.value().value())
                );
            } else if constexpr (Memory<Op2> && Immediate<typename Op2::value_type>) {
                return internal::encode<Id, Op1, Op2>(
                        desc,
                        opcode,
                        encode_modrm(op1, op2),
                        encode_sib_nodisp(op1, op2),
                        static_cast<std::uint32_t>(op2.value().value())
                );
            } else {
                return internal::encode<Id, Op1, Op2>(
                        desc,
                        opcode,
                        encode_modrm(op1, op2)
                );
            }
        }
    }

    template <e_instruction_id Id, typename Op1, typename Op2> requires Integer<Op2>
    consteval auto encode_alu(instruction_desc desc, const Op1& op1, const Op2& op2) {
        return encode_alu<Id>(desc, op1, immediate<typename truncate_as<Op1>::type>(op2));
    }

    template <typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Register<Op2> || Memory<Op2> ||Immediate<Op2>)
    consteval auto encode_opcode_bt(const std::uint8_t& opcode) {
        return static_cast<std::uint8_t>(
                (opcode & 0b11111110) +
                (!Immediate<Op2> ? 0b01 : 0b00)// setup bit `s`
        );
    }

    template <e_instruction_id Id, typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Register<Op2> || Memory<Op2> || Immediate<Op2>)
    consteval auto encode_bt(instruction_desc desc, Op1 op1, Op2 op2) {
        auto id = desc.id();
        auto opcode = desc.primary_opcode();

        if constexpr (Immediate<Op2>) {
            // Immediate src use 0xBA opcode
            opcode = 0xBA;

            return internal::encode<Id, Op1, Op2>(
                    desc, opcode, encode_modrm(opcodeext_bt(id), op1, op2), op2.value()
            );
        } else {
            opcode = encode_opcode_bt<Op1, Op2>(opcode);

            return internal::encode<Id, Op1, Op2>(
                    desc, opcode, encode_modrm(op1, op2)
            );
        }
    }

    template <e_instruction_id Id, typename Op1, typename Op2> requires Integer<Op2>
    consteval auto encode_bt(instruction_desc desc, const Op1& op1, const Op2& op2) {
        return encode_bt<Id>(desc, op1, immediate<std::uint8_t>(op2));
    }

    template <e_instruction_id Id, typename Op1>
    consteval auto encode_call(instruction_desc desc, const Op1& op1) {
        auto id = desc.id();
        auto opcode = desc.primary_opcode();

        if constexpr (Immediate<Op1>) {
            opcode = 0xE8;

            return internal::encode<Id, Op1, Void>(
                    desc, opcode, op1.value()
            );
        } else {
            return internal::encode<Id, Op1, Void>(
                    desc, opcode, encode_modrm(opcodeext_ff(id), op1)
            );
        }
    }

    template <e_instruction_id Id, typename Op1> requires Integer<Op1>
    consteval auto encode_call(instruction_desc desc, const Op1& op1) {
        return encode_call<Id>(desc, immediate<std::uint32_t>(op1));
    }

    template <e_instruction_id Id, typename Op1> requires Immediate8<Op1>
    consteval auto encode_jcc(instruction_desc desc, Op1 op1) {
        auto opcode = desc.primary_opcode();

        return internal::encode<Id, Op1, Void>(desc, opcode, op1.value());
    }

    template <e_instruction_id Id, typename Op1> requires (Immediate<Op1> || Register<Op1> || (Memory<Op1> && Register<typename Op1::value_type>))
    consteval auto encode_jmp(instruction_desc desc, Op1 op1) {
        auto id = desc.id();
        auto opcode = desc.primary_opcode();

        if constexpr (Immediate8<Op1>) {
            opcode = static_cast<std::uint8_t>(0xeb);

            return internal::encode<Id, Op1, Void>(
                    desc, opcode, op1.value()
            );
        } else if constexpr (Register<Op1> || (Memory<Op1> && Register<typename Op1::value_type>)) {
            opcode = static_cast<std::uint8_t>(0xff);

            return internal::encode<Id, Op1, Void>(
                    desc, opcode, encode_modrm(opcodeext_ff(id), op1)
            );
        } else if constexpr (Immediate<Op1>) {
            return internal::encode<Id, Op1, Void>(
                    desc, opcode, op1.value()
            );
        }
    }

    template <int Len>
    consteval auto encode_nop() {
        if constexpr (Len == 1) {
            return std::experimental::make_array<std::uint8_t>(0x90);
        } else if constexpr (Len == 2) {
            return std::experimental::make_array<std::uint8_t>(0x66, 0x90);
        } else if constexpr (Len == 3) {
            return std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x00);
        } else if constexpr (Len == 4) {
            return std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x40, 0x00);
        } else if constexpr (Len == 5) {
            return std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x44, 0x00, 0x00);
        } else if constexpr (Len == 6) {
            return std::experimental::make_array<std::uint8_t>(0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00);
        } else if constexpr (Len == 7) {
            return std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00);
        } else if constexpr (Len == 8) {
            return std::experimental::make_array<std::uint8_t>(0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00);
        } else if constexpr (Len == 9) {
            return std::experimental::make_array<std::uint8_t>(0x66, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00);
        }
    }

    template <typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Register<Op2> || Memory<Op2> || Immediate<Op2>)
    consteval auto encode_opcode_mov(const std::uint8_t& opcode) {
        return static_cast<std::uint8_t>(
                (opcode & 0b11111110) +
                (Op2::size > 8 ? 0b01 : 0b00)// setup bit `s`
        );
    }

    template <e_instruction_id Id, typename Op1, typename Op2> requires (Register<Op1> || Memory<Op1>) && (Register<Op2> || Memory<Op2> || Immediate<Op2>)
    consteval auto encode_mov(instruction_desc desc, Op1 op1, Op2 op2) {
        auto opcode = desc.primary_opcode();

        if constexpr (Immediate<Op2>) {
            if constexpr (Id != e_instruction_id::movabs) {
                opcode = encode_opcode_mov<Op1, Op2>(0xC6);
                return internal::encode<Id, Op1, Op2>(desc, opcode, encode_modrm(op1), op2.value());
            } else {
                return internal::encode<Id, Op1, Op2>(desc, opcode, op2.value());
            }
        } else {
            opcode = encode_opcode_mov<Op1, Op2>(opcode);
            return internal::encode<Id, Op1, Op2>(desc, opcode, encode_modrm(op1, op2));
        }
    }

    template <e_instruction_id Id, typename Op1, typename Op2> requires Integer<Op2>
    consteval auto encode_mov(instruction_desc desc, const Op1& op1, const Op2& op2) {
        if constexpr (Id == e_instruction_id::movabs) {
            return encode_mov<Id>(desc, op1, immediate<std::uint64_t>(op2));
        } else {
            return encode_mov<Id>(desc, op1, immediate<typename truncate_as<Op1>::type>(op2));
        }
    }

    template <e_instruction_id Id, typename Op1> requires Register<Op1>
    consteval auto encode_pop(instruction_desc desc, const Op1& op1) {
        auto primary_opcode = desc.primary_opcode();

        return std::experimental::make_array<std::uint8_t>(encode_opcode_pushpop(primary_opcode, op1));
    }

    template <e_instruction_id Id, typename Op1> requires (Register<Op1> || (Immediate<Op1> && (Op1::size == 8 || Op1::size == 32)))
    consteval auto encode_push(instruction_desc desc, const Op1& op1) {
        auto primary_opcode = desc.primary_opcode();

        if constexpr (Immediate<Op1>) {
            primary_opcode = 0x68;

            if constexpr (Immediate8<Op1>) {
                primary_opcode = 0x6A;
            }

            return internal::encode<Id, Op1, Void>(desc, primary_opcode, op1.value());
        } else if constexpr (Register<Op1>) {
            return std::experimental::make_array<std::uint8_t>(encode_opcode_pushpop(primary_opcode, op1));
        }
    }

    template <e_instruction_id Id>
    consteval auto encode_push(instruction_desc desc, const std::uint32_t& val) {
        return encode_push<Id, imm32>(desc, imm32(val));
    }

    template <e_instruction_id Id, typename Op1> requires Immediate<Op1>
    consteval auto encode_ret(instruction_desc desc, const Op1& op1) {
        auto value = static_cast<std::uint16_t>(op1.value());

        auto opcode = static_cast<std::uint8_t>(desc.primary_opcode() - 1);
        return internal::encode<Id, Op1, Void>(desc, opcode, value);
    }

    template <e_instruction_id Id, typename Op1> requires Integer<Op1>
    consteval auto encode_ret(instruction_desc desc, const Op1& op1) {
        return encode_ret<Id>(desc, immediate<std::uint16_t>(op1));
    }

    template <e_instruction_id Id, typename Op1, typename Op2>
    consteval auto encode(const Op1& op1, const Op2& op2) {
        constexpr auto desc = find_instruction_desc<Id>();

        if constexpr (desc.encoding() == e_encoding::alu) {
            return encode_alu<Id>(desc, op1, op2);
        } else if constexpr (desc.encoding() == e_encoding::bt) {
            return encode_bt<Id>(desc, op1, op2);
        } else if constexpr (desc.encoding() == e_encoding::mov) {
            return encode_mov<Id>(desc, op1, op2);
        } else {
            static_assert("Failed to encode instruction");
        }
    }

    template <e_instruction_id Id, typename Op1>
    consteval auto encode(const Op1& op1) {
        constexpr auto desc = find_instruction_desc<Id>();

        if constexpr (desc.encoding() == e_encoding::ret) {
            return encode_ret<Id>(desc, op1);
        } else if constexpr (desc.encoding() == e_encoding::call) {
            return encode_call<Id>(desc, op1);
        } else if constexpr (desc.encoding() == e_encoding::pop) {
            return encode_pop<Id>(desc, op1);
        } else if constexpr (desc.encoding() == e_encoding::push) {
            return encode_push<Id>(desc, op1);
        } else if constexpr (desc.encoding() == e_encoding::jcc) {
            return encode_jcc<Id>(desc, op1);
        } else if constexpr (desc.encoding() == e_encoding::jmp) {
            return encode_jmp<Id>(desc, op1);
        } else {
            static_assert("Failed to encode instruction");
        }
    }

    template <e_instruction_id Id>
    consteval auto encode() {
        constexpr auto desc = find_instruction_desc<Id>();
        constexpr auto size = (desc.prefix() != 0) + (desc.prefix_0f() != 0) + 1 /* _primary_opcode */ + (desc.secondary_opcode() != 0);

        std::array<std::uint8_t, size> arr {};

        int i = 0;

        if (desc.prefix() != 0) {
            arr[i++] = desc.prefix();
        }

        if (desc.prefix_0f() != 0) {
            arr[i++] = desc.prefix_0f();
        }

        if (desc.primary_opcode() != 0) {
            arr[i++] = desc.primary_opcode();
        }

        if (desc.secondary_opcode() != 0) {
            arr[i++] = desc.secondary_opcode();
        }

        return arr;
    }

    template <e_instruction_id Id, typename ...Args>
    consteval auto encode(Args&& ...args) {
        return encode<Id, Args...>(std::forward<Args>(args)...);
    }
}