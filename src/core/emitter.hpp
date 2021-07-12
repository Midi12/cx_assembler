#pragma once

#include <cstdint>
#include <tuple>

namespace cx_assembler::core {

    template <typename T, typename E, int Size>
    concept Uint8Array = std::same_as<T, std::array<E, Size>>;

    template <typename T> requires Uint8Array<T, typename T::value_type, std::tuple_size_v<T>>
    constexpr inline void emit(T array) {
        for(int i = 0; i < sizeof(array); i++) {
            asm volatile (".byte %c0" :: [a]"i"( static_cast<std::uint8_t>(array[i])));
        }
    }

    // fallback impl, has relocatable constraint as it is mainly used for function ptr
    template <typename T>
    constexpr inline void emit(T value) {
        asm volatile (".long %c0" :: [a]"ri"(value));
    }

}