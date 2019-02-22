#pragma once

#include "allocator.h"

namespace relyst::memory {

class AllocatorLinear : public Allocator {
public:
    AllocatorLinear (void * begin, void * end);

    template <typename T, std::size_t N>
    AllocatorLinear (T (&buffer)[N]) : AllocatorLinear(buffer, buffer + N) { }

public:
    std::size_t GetRemainingBytes (std::size_t align) const;

private:
    static void * ReallocImpl (Allocator * _allocator, void * oldMem, std::size_t oldSize, std::size_t newSize, std::size_t align);

private:
    char * m_begin;
    char * m_end;
};

}

