//
// Created by Jack Davidson on 27/04/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DEBUGUTILS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DEBUGUTILS_H

//#define NDEBUG // Uncomment to disable assert, or leave it to CMAKE to do when in release mode
#include <cassert>
#include <cstdio>
#define assertm(e,msg) assert(((void)msg,e));

#ifndef NDEBUG
#define DEBUGLOG(msg) printf msg
#else
#define DEBUGLOG(msg) //Used only when ifndef NDEBUG
#endif

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DEBUGUTILS_H
