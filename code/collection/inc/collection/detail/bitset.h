/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include <core/bitwise.h>

namespace relyst::collection::bitset::detail {

template <typename Derived, typename Bit>
class BitSetBaseConst {
protected:
    const Derived & D () const { return *static_cast<const Derived *>(this); }
    bool            PrepRead (bitset::Indices) const { return true; }

public:
    std::size_t CountSet () const;
    template <typename F>
    void ForEachSet (F && f) const;
    bool TestBit (Bit bit) const;
};

template <typename Derived, typename Bit>
class BitSetBase : public BitSetBaseConst<Derived, Bit> {
protected:
    Derived & D () { return *static_cast<Derived *>(this); }
    bool      PrepWrite (bitset::Indices) { return true; }

public:
    void ClearBit (Bit bit);
    void SetBit (Bit bit);
    void SetBit (Bit bit, bool value);
    void ToggleBit (Bit bit);
};

} // namespace relyst::collection::bitset::detail

#include "inline/bitset.inl"