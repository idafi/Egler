#include "Egler.Test.hpp"

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

    ASSERT_DEATH(pool.Allocate(), ".*");
}

TEST_F(PoolTest, TestReallocateFreed)
{
    Pool<int, 5>::Ptr ptrs[5];
    for(int i = 0; i < 5; i++)
    { ptrs[i] = pool.Allocate(); }
    for(int i = 0; i < 5; i++)
    { pool.Free(ptrs[i]); }

    for(int i = 0; i < 5; i++)
    { ASSERT_NO_FATAL_FAILURE(pool.Allocate()); }
}

TEST_F(PoolTest, TestFree)
{
    auto ptr = pool.Allocate();
    pool[ptr] = 666;
    pool.Free(ptr);

    ASSERT_EQ(0, pool.Count());
    ASSERT_DEATH(pool[ptr], ".*");
}

TEST_F(PoolTest, TestFreeHandlesNotAllocated)
{
    auto ptr = pool.Allocate();
    pool.Free(ptr);
    ASSERT_NO_FATAL_FAILURE(pool.Free(ptr));
}

TEST_F(PoolTest, TestIsAllocated)
{
    auto ptr = pool.Allocate();
    ASSERT_TRUE(pool.IsAllocated(ptr));

    pool.Free(ptr);
    ASSERT_FALSE(pool.IsAllocated(ptr));
}