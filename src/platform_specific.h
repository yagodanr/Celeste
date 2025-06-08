#pragma once

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#define EXPORT_FUNC __declspec(dllexport)
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#define EXPORT_FUNC __attribute__((visibility("default")))
//not implemented
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#endif




#ifdef _WIN32
    #include <windows.h>
    typedef HMODULE SharedLibHandle;
    #define platform_load_lib(path) LoadLibraryA(path)
    #define platform_load_func(lib, name) GetProcAddress(lib, name)
    //There originally was FreeLibrary(lib) but it seems Freelibrary returns oppposite of dclose
    #define platform_free_lib(lib) !FreeLibrary(lib)
    static char* GAME_LIB_PATH = "game.dll";
    static char* GAME_RELOAD_LIB_PATH = "game_load.dll";
#else
    #include <dlfcn.h>
    typedef void* SharedLibHandle;
    #define platform_load_lib(path) dlopen(path, RTLD_NOW)
    #define platform_load_func(lib, name) dlsym(lib, name)
    #define platform_free_lib(lib) dlclose(lib)
    static char* GAME_LIB_PATH = "game.so";
    static char* GAME_RELOAD_LIB_PATH = "game_load.so";
#endif
