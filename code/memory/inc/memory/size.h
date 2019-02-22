#pragma once

#include <cstddef>

namespace relyst::memory {
constexpr std::size_t kBytesPerKibibyte = 1024;
constexpr std::size_t kBytesPerMebibyte = 1024 * kBytesPerKibibyte;
constexpr std::size_t kBytesPerGibibyte = 1024 * kBytesPerMebibyte;
constexpr std::size_t kBytesPerTebibyte = 1024 * kBytesPerGibibyte;
}

namespace relyst::memory::literals {
constexpr inline std::size_t operator""_KiB (long double v) { return std::size_t(v * kBytesPerKibibyte); }
constexpr inline std::size_t operator""_MiB (long double v) { return std::size_t(v * kBytesPerMebibyte); }
constexpr inline std::size_t operator""_GiB (long double v) { return std::size_t(v * kBytesPerGibibyte); }
constexpr inline std::size_t operator""_TiB (long double v) { return std::size_t(v * kBytesPerTebibyte); }
}

namespace relyst { using namespace ::relyst::memory::literals; }