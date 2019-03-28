/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include <new>

namespace relyst::memory {

inline void * Allocator::Alloc (std::size_t newSize, std::size_t align) {
    return Realloc(nullptr, 0, newSize, align);
}

template <typename T>
inline T * Allocator::Alloc () {
    return new(Alloc(sizeof(T), alignof(T))) T();
}

template <typename T>
inline T * Allocator::AllocN (std::size_t count) {
    return new(Alloc(sizeof(T) * count, alignof(T))) T[count];
}

inline void * Allocator::Realloc (void * oldMem, std::size_t oldSize, std::size_t newSize, std::size_t align) {
    return m_reallocFunc(this, oldMem, oldSize, newSize, align);
}

} // namespace relyst::memory
