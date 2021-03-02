//
// Created by Jack Davidson on 27/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DEBUGUTILS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DEBUGUTILS_H

//#define NDEBUG // Uncomment to disable assert, or leave it to CMAKE to do when in release mode
#include <filesystem>
#include <cstdio>

#if !defined(NDEBUG)
    #if defined(_WIN32)
        #define DEBUGBREAK() __debugbreak()
    #elif defined(__APPLE__)
        #include <csignal>
        #define DEBUGBREAK() raise(SIGTRAP)
    #endif
#else
    #define DEBUGBREAK()
#endif

#define ASSERT(check,msg) {if(check == 0) {printf("Assert Failed: %s, in file: %s at line %d.\nError: %s",#check,std::filesystem::path(__FILE__).filename().string().c_str(),__LINE__,static_cast<std::string>(msg).c_str())/*todo: Had to cast to string to avoid complex object issues, need to create proper logger that will handle this easier.*/; DEBUGBREAK();}}

#ifndef NDEBUG
#define DEBUGLOG(msg) printf msg
#else
#define DEBUGLOG(msg) //Used only when ifndef NDEBUG
#endif

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DEBUGUTILS_H
