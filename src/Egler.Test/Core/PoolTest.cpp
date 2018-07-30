#include "../Egler.Test.hpp"

namespace Egler::Core
{
    class PoolTest : public testing::Test
    {
        protected:
            Pool<int, 5> pool;
    };

    TEST_F(PoolTest, TestCtorWithExistingValues)
    {
        int values[3] = { 2, 4, 6 };
        auto p = Pool<int, 5>(values, 3);

        ASSERT_EQ(2, p[p.Allocate()]);
        ASSERT_EQ(4, p[p.Allocate()]);
        ASSERT_EQ(6, p[p.Allocate()]);
        ASSERT_EQ(0, p[p.Allocate()]);
        ASSERT_EQ(0, p[p.Allocate()]);
    }

    TEST_F(PoolTest, TestAllocate)
    {
        auto ptr = pool.Allocate();
        pool[ptr] = 666;

        ASSERT_EQ(1, pool.Count());
        ASSERT_EQ(666, pool[ptr]);
    }

    TEST_F(PoolTest, TestAllocateFailsWhenFull)
    {
        for(int i = 0; i < pool.Capacity(); i++)
        { pool.Allocate(); }

        ASSERT_THROW(pool.Allocate(), InvalidOperationException);
    }

    TEST_F(PoolTest, TestReallocateFreed)
    {
        Pool<int, 5>::Ptr ptrs[5];
        for(int i = 0; i < 5; i++)
        { ptrs[i] = pool.Allocate(); }
        for(int i = 0; i < 5; i++)
        { pool.Free(ptrs[i]); }

        for(int i = 0; i < 5; i++)
        { ASSERT_NO_THROW(pool.Allocate()); }
    }

    TEST_F(PoolTest, TestFree)
    {
        auto ptr = pool.Allocate();
        pool[ptr] = 666;
        pool.Free(ptr);

        ASSERT_EQ(0, pool.Count());
        ASSERT_THROW(pool[ptr], OutOfRangeException);
    }

    TEST_F(PoolTest, TestFreeHandlesNotAllocated)
    {
        auto ptr = pool.Allocate();
        pool.Free(ptr);
        ASSERT_NO_THROW(pool.Free(ptr));
    }

    TEST_F(PoolTest, TestIsAllocated)
    {
        auto ptr = pool.Allocate();
        ASSERT_TRUE(pool.IsAllocated(ptr));

        pool.Free(ptr);
        ASSERT_FALSE(pool.IsAllocated(ptr));
    }

    TEST_F(PoolTest, TestClear)
    {
        auto ptrA = pool.Allocate();
        auto ptrB = pool.Allocate();
        pool[ptrA] = 666;
        pool[ptrB] = 69;

        pool.Clear();

        ASSERT_EQ(0, pool.Count());
        ASSERT_FALSE(pool.IsAllocated(ptrA));
        ASSERT_FALSE(pool.IsAllocated(ptrB));
    }

    TEST_F(PoolTest, TestRangeItr)
    {
        auto ptrA = pool.Allocate();
        auto ptrB = pool.Allocate();
        auto ptrC = pool.Allocate();
        
        pool[ptrA] = 666;
        pool.Free(ptrB);
        pool[ptrC] = 69;

        int ct = 0;
        for(auto& i : pool)
        {
            if(ct == 0)
            { ASSERT_EQ(666, i); }
            else if(ct == 1)
            { ASSERT_EQ(69, i); }

            ct++;
        }

        ASSERT_EQ(2, ct);
    }
}