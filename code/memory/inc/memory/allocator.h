/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include <cstddef>

namespace relyst::memory {

class Allocator {
    using ReallocFunc = void * (*)(Allocator * _allocator, void * oldMem, std::size_t oldSize, std::size_t newSize, std::size_t align);
    ReallocFunc m_reallocFunc;

protected:
    Allocator (ReallocFunc reallocFunc) : m_reallocFunc(reallocFunc) { }

public:
    inline void * Realloc (void * oldMem, std::size_t oldSize, std::size_t newSize, std::size_t align);
    inline void * Alloc (std::size_t newSize, std::size_t align);

public: // Templated helpers
    template <typename T>
    inline T * Alloc ();
};

} // relyst::memory

#include "inline/allocator.inl"