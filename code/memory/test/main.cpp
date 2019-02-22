/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

 // Crap for leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

void MemoryLeakDetection () {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

#include <memory/allocator_linear.h>
#include <iostream>
#include <array>

#include <vector>

template <typename T>
struct StlAllocator {
    typedef T value_type;
    relyst::memory::Allocator * alloc;
    StlAllocator (relyst::memory::Allocator & alloc) : alloc(&alloc) { }
    template <typename U>
    StlAllocator (const StlAllocator<U> & rhs) : alloc(rhs.alloc) { }
    T * allocate (std::size_t n) { return static_cast<T*>(alloc->Realloc(nullptr, 0, n * sizeof(T), alignof(T))); }
    void deallocate (T * p, std::size_t n) { alloc->Realloc(p, n * sizeof(T), 0, alignof(T)); }
};

int main()
{
    MemoryLeakDetection();

    char buffer[1024];
    auto allocator = relyst::memory::AllocatorLinear(buffer);

    auto dumb = std::vector<int, StlAllocator<int>>(StlAllocator<int>(allocator));
    dumb.push_back(10);
    dumb.push_back(987);
    dumb.push_back(123);
    dumb.push_back(555);

	return 0;
}