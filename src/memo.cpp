#include "memo.h"


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

char* allocate_bump(size_t size, BumpAllocator* bumpAllocator) {
    // 20 -> 24
    // 16 -> 16
    // 8 -> 8
    // 1 -> 8
    // 9 -> 16
    // 8 * ((size+7) // 8)
    size_t alignedSize = (size+BUMP_ALLOCATOR_ALIGNMENT) & (~BUMP_ALLOCATOR_ALIGNMENT);
    if(bumpAllocator->used + alignedSize > bumpAllocator->capacity) {
        SM_ASSERT(false, "BumpAllocatorOverflow");
        return nullptr;
    }

    char* result = bumpAllocator->memory + bumpAllocator->used;
    bumpAllocator->used += alignedSize;

    return result;
}


// #############################################################################
//                           File I/O
// #############################################################################
long long get_timestamp(const char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    struct stat file_stat = {};
    stat(filePath, &file_stat);
    return file_stat.st_mtime;
}

bool file_exists(const char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    auto file = fopen(filePath, "rb");
    if(!file)
    {
        return false;
    }
    fclose(file);

    return true;
}

long get_file_size(const char* filePath)
{
    SM_ASSERT(filePath, "No filePath supplied!");

    long fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file)
    {
        SM_ERROR("Failed opening File: %s", filePath);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    return fileSize;
}


char* read_file(const char* filePath, long* fileSize, char* buffer) {
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(fileSize, "No fileSize supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");

    *fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file) {
        SM_ASSERT(false, "Failed to open file during read_file(%s)", filePath);
        return nullptr;
    }
    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // memset(buffer, 0, *fileSize);
    fread(buffer, sizeof(char), *fileSize, file);
    fclose(file);

    return buffer;
}

char* read_file(const char* filePath, long* fileSize, BumpAllocator* bumpAllocator) {
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(fileSize, "No fileSize supplied!");
    SM_ASSERT(bumpAllocator, "No bumpAllocator supplied!");


    *fileSize = 0;
    long fileSize2 = get_file_size(filePath);
    if(!fileSize2) {
        SM_WARN("File %s empty during reading", filePath);
    }

    return read_file(filePath, fileSize, allocate_bump(*fileSize+1, bumpAllocator));
}


bool write_file(const char* filePath, char* buffer, const int size) {
    SM_ASSERT(filePath, "No filePath supplied!");
    SM_ASSERT(buffer, "No buffer supplied!");


    auto file = fopen(filePath, "wb");
    if(!file) {
        SM_ASSERT(false, "Failed to open file during write_file(%s)", filePath);
        return false;
    }

    bool result = fwrite(buffer, sizeof(char), size, file);
    fclose(file);

    return result;
}


bool copy_file(const char* fromPath, const char* toPath, char* buffer) {
    long fileSize = 0;
    char* fromFile = read_file(fromPath, &fileSize, buffer);

    return write_file(toPath, fromFile, fileSize);
}


bool copy_file(const char* fromPath, const char* toPath, BumpAllocator* bumpAllocator) {
    long fileSize = 0;
    char* fromFile = read_file(fromPath, &fileSize, bumpAllocator);

    return write_file(toPath, fromFile, fileSize);
}