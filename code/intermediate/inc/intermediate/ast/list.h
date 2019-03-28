/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include <memory/allocator.h>

namespace relyst::intermediate::ast {

/*
 * This is a destructor-less list that allocates memory it does not free. This is intentional.
 * Large amounts of lists will be allocated and deallocated at the same time in
 * the compliation process, so instead the lists will just be bound to allocators
 * with valid lifetimes.
 */

template <typename T>
class List {
    T * m_begin = nullptr;
    T * m_end = nullptr;
    T * m_reservationEnd = nullptr;

public:
    List () { }
    List (memory::Allocator & alloc, std::size_t maxItems) : m_begin(alloc.AllocN<T>(maxItems)), m_end(m_begin), m_reservationEnd(m_begin + maxItems) { }

public:
    T *       begin () { return m_begin; }
    const T * begin () const { return m_begin; }
    T *       end () { return m_end; }
    const T * end () const { return m_end; }
    T * Push (const T & v) {
        if (m_end >= m_reservationEnd)
            return nullptr;
        *m_end = v;
        return m_end++;
    }
};

} // namespace relyst::intermediate::ast