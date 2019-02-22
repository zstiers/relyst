/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include <collection/bitset.h>
#include <memory/allocator_linear.h>

#include <iostream>

int main() {
    using namespace relyst;
    using namespace relyst::collection;
    using namespace relyst::memory;

    relyst::collection::bitset::Block blocks[relyst::collection::bitset::BitsToBlocks(129)] = { };
    BitSetSpan span(std::begin(blocks), std::end(blocks));
    span.ToggleBit(10);
    span.ToggleBit(49);
    span.ToggleBit(87);
    span.ToggleBit(92);
    span.ForEachSet([](auto index) { std::cout << index << "\n"; });

    BitSetFixed<65> fixed;
    fixed.SetBit(3);
    fixed.SetBit(4, true);
    fixed.SetBit(3, false);
    fixed.SetBit(9);
    fixed.SetBit(53);
    fixed.SetBit(64);
    fixed.ForEachSet([](auto index) { std::cout << index << "\n"; });

    BitSetView view(fixed);
    view.ForEachSet([](auto index) { std::cout << index << "\n"; });
}