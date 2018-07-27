#pragma once

// - - - - - -
// shared includes and definitions
// - - - - - -

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define intern static
typedef int8_t sbyte;
typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;

#define M_PI 3.14159265358979323846

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define Clamp(value, lower, upper) (min(max((value), (lower)), (upper)))
#define randf() ((float)(rand()) / (float)(RAND_MAX))

#define FlagSet(mask, flag) ((mask) |= (flag))
#define FlagClear(mask, flag) ((mask) &= ~(flag))
#define FlagTest(mask, flag) (((mask) & (flag)) == (flag))

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Console.hpp"
