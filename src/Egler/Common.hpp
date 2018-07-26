#pragma once

// - - - - - -
// shared includes and definitions
// - - - - - -

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>

#define intern static

#define M_PI 3.14159265358979323846

#define FlagSet(mask, flag) ((mask) |= (flag))
#define FlagClear(mask, flag) ((mask) &= ~(flag))
#define FlagTest(mask, flag) (((mask) & (flag)) == (flag))