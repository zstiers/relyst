/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "../bitwise.h"

#ifdef _MSC_VER
#include <intrin.h>
#include <cstddef>
#include <limits>

namespace relyst::core::bitwise {

inline std::size_t CountLeadingZeroes (BitScan value) {
    unsigned long leading_zero = 0;
    if (_BitScanReverse(&leading_zero, value))
        return (std::numeric_limits<BitScan>::digits - 1) - leading_zero;
    else
        return std::numeric_limits<BitScan>::digits;
}

inline std::size_t CountLeadingZeroes (BitScan64 value) {
    unsigned long leading_zero = 0;
    if (_BitScanReverse64(&leading_zero, value))
        return (std::numeric_limits<BitScan64>::digits - 1) - leading_zero;
    else
        return std::numeric_limits<BitScan64>::digits;
}

inline std::size_t CountSetBits (BitScan value) {
    return __popcnt(value);
}

inline std::size_t CountSetBits (BitScan64 value) {
    return __popcnt64(value);
}

inline std::size_t CountTrailingZeroes (BitScan value) {
    unsigned long trailing_zero = 0;
    if (_BitScanForward(&trailing_zero, value))
        return trailing_zero;
    else
        return std::numeric_limits<BitScan>::digits;
}

inline std::size_t CountTrailingZeroes (BitScan64 value) {
    unsigned long trailing_zero = 0;
    if (_BitScanForward64(&trailing_zero, value))
        return trailing_zero;
    else
        return std::numeric_limits<BitScan64>::digits;
}

} // relyst::core::bitwise

#endif