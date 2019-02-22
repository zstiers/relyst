/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include <memory/allocator_linear.h>
#include <memory>

// TODO : Fix up this file to use std::align. It has some annoying type requirements so I'll end up wrapping it.

namespace relyst::memory {

AllocatorLinear::AllocatorLinear (void * begin, void * end)
    : Allocator(&ReallocImpl)
    , m_begin(static_cast<char *>(begin))
    , m_end(static_cast<char *>(end))
{
}

std::size_t AllocatorLinear::GetRemainingBytes (std::size_t align) const {
    const auto alignOffsetOver = uintptr_t(m_begin) % align;
    const auto alignOffset = alignOffsetOver ? align - alignOffsetOver : 0;
    const auto expectedBegin = m_begin + alignOffset;
    return expectedBegin < m_end ? m_end - expectedBegin : 0;
}

void * AllocatorLinear::ReallocImpl (Allocator * _allocator, void * oldMem, std::size_t oldSize, std::size_t newSize, std::size_t align) {
    auto allocator = static_cast<AllocatorLinear *>(_allocator);

    if (!newSize)
        return nullptr;

    // TODO: Log that this is an invalid operation
    if (oldMem && newSize)
        return nullptr;

    const auto alignOffsetOver = uintptr_t(allocator->m_begin) % align;
    const auto alignOffset = alignOffsetOver ? align - alignOffsetOver : 0;
    const auto expectedBegin = allocator->m_begin + alignOffset;
    const auto expectedEnd = expectedBegin + newSize;
    if (expectedEnd > allocator->m_end)
        return nullptr;
    allocator->m_begin = expectedEnd;
    return expectedBegin;
}

}