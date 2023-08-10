#pragma once

// identify operating system and toolchain
#if defined(WIN64) || defined(_WIN64) || defined(WIN32)
#define MP34U_PLATFORM_WIN64

#elif defined(__linux__)
#define MP34U_PLATFORM_LINUX

#else
    #error "Platform not supported"
#endif


#if defined(_MSC_VER)
#define MP34U_COMPILER_MSVC

    // This is some bs right here but it works
    #define and &&
    #define or ||

#elif defined(__MINGW64__)
#define MP34U_COMPILER_MINGW_W64

#elif defined(__MINGW32__)
#define MP34U_COMPILER_MINGW_W64

#elif defined(__GNUC__)
    #define MP34U_COMPILER_GCC

#else
    #error "Compiler is not supported"
#endif