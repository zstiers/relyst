#pragma once

#include <cstddef>

namespace relyst::core::bitwise {

#ifdef _MSC_VER
using BitScan   = unsigned long;
using BitScan64 = unsigned __int64;
#endif

using BitScanFast = BitScan64;

inline std::size_t CountLeadingZeroes (BitScan value);
inline std::size_t CountLeadingZeroes (BitScan64 value);
inline std::size_t CountSetBits (BitScan value);
inline std::size_t CountSetBits (BitScan64 value);
inline std::size_t CountTrailingZeroes (BitScan value);
inline std::size_t CountTrailingZeroes (BitScan64 value);

} // relyst::core::bitwise

#include "inline/bitwise.inl"