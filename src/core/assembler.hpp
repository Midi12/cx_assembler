#pragma once

#include <numeric>
#include <array>

namespace cx_assembler::core {

    // https://stackoverflow.com/questions/25068481/c11-constexpr-flatten-list-of-stdarray-into-array
    template <typename T, size_t... sz>
    constexpr auto assemble(std::array<T, sz>... ar) {
        constexpr size_t NB_ARRAY = sizeof...(ar);

        T* datas[NB_ARRAY] = {&ar[0]...};
        constexpr size_t lengths[NB_ARRAY] = {ar.size()...};

        constexpr size_t FLATLENGTH = std::accumulate(lengths, lengths + NB_ARRAY, 0);

        std::array<T, FLATLENGTH> flat_a = {0};

        int index = 0;
        for(int i = 0; i < NB_ARRAY; i++)
        {
            for(int j = 0; j < lengths[i]; j++)
            {
                flat_a[index] = datas[i][j];
                index++;
            }
        }

        return flat_a;
    }

}