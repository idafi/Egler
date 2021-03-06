#include "Egler.Test.hpp"

namespace Egler
{
    class CheckTest : public testing::Test
    { };

    TEST_F(CheckTest, TestCheck)
    {
        ASSERT_THROW(Check(false), BadArgumentException);
        ASSERT_NO_THROW(Check(true));
    }

    TEST_F(CheckTest, TestCheckPtr)
    {
        int i = 666;
        int *p = &i;

        ASSERT_THROW(CheckPtr(nullptr), NullPtrException);
        ASSERT_NO_THROW(CheckPtr(p));
    }

    TEST_F(CheckTest, TestCheckID)
    {
        ASSERT_THROW(CheckID(0), BadArgumentException);
        ASSERT_THROW(CheckID(-1), BadArgumentException);
        ASSERT_NO_THROW(CheckID(1));
    }

    TEST_F(CheckTest, TestCheckSign)
    {
        ASSERT_THROW(CheckSign(-1), OutOfRangeException);
        ASSERT_THROW(CheckSign(-0.00001f), OutOfRangeException);
        ASSERT_NO_THROW(CheckSign(1));
        ASSERT_NO_THROW(CheckSign(0));
    }

    TEST_F(CheckTest, TestCheckIndex)
    {
        ASSERT_THROW(CheckIndex(5, 5), OutOfRangeException);
        ASSERT_THROW(CheckIndex(6, 5), OutOfRangeException);
        ASSERT_THROW(CheckIndex(-1, 5), OutOfRangeException);
        ASSERT_NO_THROW(CheckIndex(0, 5));
        ASSERT_NO_THROW(CheckIndex(4, 5));
    }

    TEST_F(CheckTest, TestCheckRange)
    {
        ASSERT_THROW(CheckRange(6, 5), OutOfRangeException);
        ASSERT_THROW(CheckRange(-1, 5), OutOfRangeException);
        ASSERT_NO_THROW(CheckRange(0, 5));
        ASSERT_NO_THROW(CheckRange(5, 5));
    }
}