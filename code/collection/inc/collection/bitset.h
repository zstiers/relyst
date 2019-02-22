#pragma once

#include <core/bitwise.h>
#include <cstddef>
#include <limits>

namespace relyst::collection::bitset {

using Block = core::bitwise::BitScanFast;
struct Indices { std::size_t block; std::size_t offset; };
constexpr std::size_t BitToBlock (std::size_t bit)    { return bit / std::numeric_limits<Block>::digits; }
constexpr Indices     BitToIndices (std::size_t bit)  { const auto block = BitToBlock(bit); return { block, bit - block * std::numeric_limits<Block>::digits }; }
constexpr std::size_t BitsToBlocks (std::size_t bits) { return BitToBlock(bits - 1) + 1; }

} // relyst::collection::bitset

#include "detail/bitset.h"

namespace relyst::collection::bitset::concrete {

template <std::size_t N, typename Bit = std::size_t>
class BitSetFixed : public detail::BitSetBase<BitSetFixed<N, Bit>, Bit> {
    static constexpr auto kBlocks = BitsToBlocks(N);
    Block m_buffer[kBlocks] = { };

public:
    constexpr Block *       BlockBegin ()       { return m_buffer; }
    constexpr Block *       BlockEnd ()         { return m_buffer + kBlocks; }
    constexpr const Block * BlockBegin () const { return m_buffer; }
    constexpr const Block * BlockEnd () const   { return m_buffer + kBlocks; }
};

template <typename Bit = std::size_t>
class BitSetSpan : public detail::BitSetBase<BitSetSpan<Bit>, Bit> {
    bitset::Block * m_begin;
    bitset::Block * m_end;

public:
    constexpr bitset::Block *       BlockBegin ()       { return m_begin; }
    constexpr bitset::Block *       BlockEnd ()         { return m_end; }
    constexpr const bitset::Block * BlockBegin () const { return m_begin; }
    constexpr const bitset::Block * BlockEnd () const   { return m_end; }

public:
    constexpr BitSetSpan () : m_begin(nullptr), m_end(nullptr) { }
    constexpr BitSetSpan (bitset::Block * begin, bitset::Block * end) : m_begin(begin), m_end(end) { }
};

template <typename Bit = std::size_t>
class BitSetView : public detail::BitSetBaseConst<BitSetView<Bit>, Bit> {
    const bitset::Block * m_begin;
    const bitset::Block * m_end;

public:
    constexpr const bitset::Block * BlockBegin () const { return m_begin; }
    constexpr const bitset::Block * BlockEnd () const   { return m_end; }

public:
    constexpr BitSetView () : m_begin(nullptr), m_end(nullptr) { }
    constexpr BitSetView (const bitset::Block * begin, const bitset::Block * end) : m_begin(begin), m_end(end) { }

    template <typename T>
    constexpr BitSetView (const T & viewable) : m_begin(viewable.BlockBegin()), m_end(viewable.BlockEnd()) { }
};

} // relyst::collection::bitset::concrete

namespace relyst::collection         { using namespace ::relyst::collection::bitset::concrete; }
namespace relyst::collection::bitset { using namespace ::relyst::collection::bitset::concrete; }

#include "inline/bitset.inl"