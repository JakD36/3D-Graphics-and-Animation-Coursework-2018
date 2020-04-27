//
// Created by Jack Davidson on 27/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_LOGUTILS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_LOGUTILS_H

//#define NDEBUG // Uncomment to disable assert, or leave it to CMAKE to do when in release mode
#include <cassert>
#include <cstdio>
#define assertm(e,msg) assert(((void)msg,e));

#ifndef NDEBUG
#define LOG(msg) printf msg
#else
#define LOG(msg) //Used only when ifndef NDEBUG
#endif

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_LOGUTILS_H
