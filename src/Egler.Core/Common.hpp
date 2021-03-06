#pragma once

// - - - - - -
// shared includes and definitions
// - - - - - -

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <memory>

#define intern static
#define EGAPI __declspec(dllexport)

namespace Egler
{
    typedef int8_t sbyte;
    typedef uint8_t byte;
    typedef uint16_t ushort;
    typedef uint32_t uint;
    typedef uint64_t ulong;
}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))
#define Clamp(value, lower, upper) (Min(Max((value), (lower)), (upper)))
#define RandF() ((float)(rand()) / (float)(RAND_MAX))
#define Deg2Rad(degrees) ((degrees) * ((M_PI) / 180))
#define Rad2Deg(radians) ((radians) * (180.0 / (M_PI)))

#define FlagSet(mask, flag) ((mask) |= (flag))
#define FlagClear(mask, flag) ((mask) &= ~(flag))
#define FlagTest(mask, flag) (((mask) & (flag)) == (flag))

#include "Exceptions.hpp"
#include "Check.hpp"