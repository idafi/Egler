#pragma once

#include "Common.hpp"

#define _Check(cond, exception, msg, ...) \
    if(!(cond)) \
    { throw exception("%s: %s(): line %u\n\t%s", __FILE__, __func__, __LINE__, msg, ##__VA_ARGS__); }

#define Check(cond) _Check((cond), BadArgumentException, "!! Condition check ('" #cond "') failed !!")
#define CheckPtr(ptr) _Check((ptr) != nullptr, NullPtrException, "!! Pointer '" #ptr "' is null !!")
#define CheckIndex(index, len) _Check(((index) > -1) && ((index) < (len)), OutOfRangeException, \
    "!! Array index '" #index "' is out of range (between 0 and %i)", (len) - 1)
#define CheckSign(n) _Check((n) >= 0, OutOfRangeException, "!! Value of '" #n "' is negative (%i)", (n))