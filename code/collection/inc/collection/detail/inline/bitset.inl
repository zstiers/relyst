/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "../bitset.h"
#include <cstring>

namespace relyst::collection::bitset::detail {

template <typename Derived, typename Bit>
std::size_t BitSetBaseConst<Derived, Bit>::CountSet () const {
    std::size_t total = 0;
    for (auto currPtr = D().BlockBegin(), endPtr = D().BlockEnd(); currPtr < endPtr; ++currPtr)
        total += core::bitwise::CountSetBits(*currPtr);
    return total;
}

template <typename Derived, typename Bit>
template <typename F>
void BitSetBaseConst<Derived, Bit>::ForEachSet (F && f) const {
    std::size_t offset = 0;
    for (auto currPtr = D().BlockBegin(), endPtr = D().BlockEnd(); currPtr < endPtr; ++currPtr, offset += std::numeric_limits<Block>::digits) {
        for (auto current = *currPtr; current;) {
            const auto bit = core::bitwise::CountTrailingZeroes(current);
            current ^= Block(1) << bit;
            f(Bit(bit + offset));
        }
    }
}

template <typename Derived, typename Bit>
bool BitSetBaseConst<Derived, Bit>::TestBit (Bit bit) const {
    auto indices = bitset::BitToIndices(bit);
    return PrepRead(indices) && D().BlockBegin()[indices.block] & (bitset::Block(1) << indices.offset);
}

template <typename Derived, typename Bit>
void BitSetBase<Derived, Bit>::ClearBit (Bit bit) {
    if (auto indices = bitset::BitToIndices(bit); PrepWrite(indices))
        D().BlockBegin()[indices.block] &= ~(bitset::Block(1) << indices.offset);
}

template <typename Derived, typename Bit>
void BitSetBase<Derived, Bit>::SetBit (Bit bit) {
    if (auto indices = bitset::BitToIndices(bit); PrepWrite(indices))
        D().BlockBegin()[indices.block] |= bitset::Block(1) << indices.offset;
}

template <typename Derived, typename Bit>
void BitSetBase<Derived, Bit>::SetBit (Bit bit, bool value) {
    value ? SetBit(bit) : ClearBit(bit);
}

template <typename Derived, typename Bit>
void BitSetBase<Derived, Bit>::ToggleBit (Bit bit) {
    if (auto indices = bitset::BitToIndices(bit); PrepWrite(indices))
        D().BlockBegin()[indices.block] ^= bitset::Block(1) << indices.offset;
}

} // namespace relyst::collection::bitset::detail