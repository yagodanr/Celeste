#pragma once

#include <cstdlib>
// Used to get the edit timestamp of files
#include <sys/stat.h>

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


BumpAllocator make_bump_allocator(size_t size);

char* allocate_bump(size_t size, BumpAllocator* bumpAllocator);


long long get_timestamp(const char* file);
bool file_exists(const char* filePath);
long get_file_size(const char* filePath);

char* read_file(const char* filePath, long* fileSize, char* buffer);
char* read_file(const char* filePath, long* fileSize, BumpAllocator* bumpAllocator);
