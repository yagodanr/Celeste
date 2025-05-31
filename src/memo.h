#pragma once

#include <cstdlib>
#include "logger.h"


#define BIT(x)  1 << x;
#define KB(x)   (unsigned long long) 1024 * x;
#define MB(x)   (unsigned long long) 1024 * KB(x);
#define GB(x)   (unsigned long long) 1024 * MB(x);


// align buffer to be a multiple of 8
#define BUMP_ALLOCATOR_ALIGNMENT 8-1


struct BumpAllocator {
    size_t capacity;
    size_t used;
    char* memory;

    ~BumpAllocator() {
        free(this->memory);
    }
};


BumpAllocator make_bump_allocator(size_t size) {
    BumpAllocator result = {};

    result.memory = (char*) calloc(size, sizeof(char));
    if(!result.memory) {
        SM_ASSERT(false, "Failed to allocate memory for the Bump");
        return BumpAllocator{};
    }

    result.capacity = size;
    return result;

}

char* allocate_bump(size_t size, BumpAllocator buffer) {
    // 20 -> 24
    // 16 -> 16
    // 8 -> 8
    // 1 -> 8
    // 9 -> 16
    // 8 * ((size+7) // 8)
    size_t alignedSize = (size+BUMP_ALLOCATOR_ALIGNMENT) & (~BUMP_ALLOCATOR_ALIGNMENT);
    if(buffer.used + alignedSize > buffer.capacity) {
        SM_ASSERT(false, "BumpAllocatorOverflow");
        return nullptr;
    }

    char* result = buffer.memory + buffer.used;
    buffer.used += alignedSize;

    return result;
}

