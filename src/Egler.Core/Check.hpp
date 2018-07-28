#pragma once

#include "Common.hpp"

#define _Check(cond, exception, msg, ...) \
    if(!(cond)) \
    { throw exception("%s: %s(): line %u\n\t%s", __FILE__, __func__, __LINE__, msg, ##__VA_ARGS__); }

#define Check(cond) _Check((cond), BadArgumentException, "!! Condition check ('" #cond "') failed !!")
#define CheckPtr(ptr) _Check((ptr) != nullptr, NullPtrException, "!! Pointer '" #ptr "' is null !!")
#define CheckID(id) _Check((id) > 0, BadArgumentException, "!! ID '" #id "' (%i) is invalid !!", id)
#define CheckSign(n) _Check((n) >= 0, OutOfRangeException, "!! Value of '" #n "' (%i) is negative !!", (n))
#define CheckIndex(index, len) _Check(((index) > -1) && ((index) < (len)), OutOfRangeException, \
    "!! Array index '" #index "' (%i) is out of range (between 0 and %i) !!", index, (len) - 1)
#define CheckRange(n, len) _Check(((n) > -1) && ((n) <= (len)), OutOfRangeException, \
    "!! Number '" #n "' (%i) is out of range (between 0 and %i) !!", n, len)
