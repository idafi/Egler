#include "Egler.Test.hpp"

class MatrixTest : public testing::Test
{
    protected:
        MatrixTest()
        {
            for(int i = 0; i < Mat4::Size; i++)
            { a[i] = i; }

            b = Mat4::Identity();
        }

        Mat4 a;
        Mat4 b;
};

TEST_F(MatrixTest, TestDefaultInit)
{
    a = Mat4();
    for(int i = 0; i < Mat4::Size; i++)
    { ASSERT_FLOAT_EQ(0, a[i]); }
}

TEST_F(MatrixTest, TestDefaultInitWithNew)
{
    Mat4 *m = new Mat4();
    for(int i = 0; i < Mat4::Size; i++)
    { ASSERT_FLOAT_EQ(0, (*m)[i]); }

    delete m;
}

TEST_F(MatrixTest, TestCopy)
{
    b = Mat4(a);

    for(int i = 0; i < Mat4::Size; i++)
    { ASSERT_FLOAT_EQ(a[i], b[i]); }
}

TEST_F(MatrixTest, TestCompareEqual)
{
    b = a;
    ASSERT_TRUE(b == a);
}

TEST_F(MatrixTest, TestCompareNotEqual)
{
    ASSERT_TRUE(b != a);
}

TEST_F(MatrixTest, TestIndexGet)
{
    for(int i = 0; i < Mat4::Size; i++)
    { ASSERT_FLOAT_EQ(i, a[i]); }
}

TEST_F(MatrixTest, TestIndexSet)
{
    a[6] = 9;
    ASSERT_FLOAT_EQ(a[6], 9);
}

TEST_F(MatrixTest, TestAdd)
{
    Mat4 c = a + a;
    for(int i = 0; i < Mat4::Size; i++)
    { ASSERT_FLOAT_EQ(c[i], i + i); }
}

TEST_F(MatrixTest, TestSubtract)
{
    for(int i = 0; i < Mat4::Size; i++)
    { b[i] = i * 2; }

    Mat4 c = b - a;
    for(int i = 0; i < Mat4::Size; i++)
    { ASSERT_FLOAT_EQ(c[i], i); }
}

TEST_F(MatrixTest, TestAddAssign)
{
	Matrix<4, 4> c = a + b;
	Matrix<4, 4> d = a;
	d += b;
	
	ASSERT_TRUE(c == d);
}

TEST_F(MatrixTest, TestSubtractAssign)
{
	Matrix<4, 4> c = b - a;
	Matrix<4, 4> d = b;
	d -= a;
	
	ASSERT_TRUE(c == d);
}

TEST_F(MatrixTest, TestMultiply)
{
	Matrix<3, 3> a;
	a[0] = 3;		a[3] = -8;		a[6] = 2.58f;
	a[1] = -83;		a[4] = 0;		a[7] = 1;
	a[2] = 646;		a[5] = -43.85f;	a[8] = -13.5f;
	
	Matrix<3, 3> b;
	b[0] = 12;		b[3] = -0.82;	b[6] = 2.225f;
	b[1] = 33;		b[4] = 35.28;	b[7] = 13;
	b[2] = -68.25f;	b[5] = 153;		b[8] = 0;
	
	Matrix<3, 3> c;
	c[0] = -404.085f;	c[3] = 110.04f;		c[6] = -97.325f;
	c[1] = -1064.25f;	c[4] = 221.06f;		c[7] = -184.675f;
	c[2] = 7226.325f;	c[5] = -4142.248f;	c[8] = 867.3f;
	
	Matrix<3, 3> d = a * b;
	
	for(int i = 0; i < 9; i++)
	{ EXPECT_FLOAT_EQ(d[i], c[i]); }
}

TEST_F(MatrixTest, TestMultiplyDifferentDimensions)
{
	Matrix<3, 3> a;
	a[0] = 3;		a[3] = -8;		a[6] = 2.58f;
	a[1] = -83;		a[4] = 0;		a[7] = 1;
	a[2] = 646;		a[5] = -43.85f;	a[8] = -13.5f;
	
	Matrix<1, 3> b;
	b[0] = 2;
	b[1] = -24.5f;
	b[2] = 1.1f;
	
	Matrix<1, 3> c;
	c[0] = 204.838f;
	c[1] = -164.9f;
	c[2] = 2351.475f;
	
	Matrix<1, 3> d = a * b;
	
	for(int i = 0; i < 3; i++)
	{ EXPECT_FLOAT_EQ(d[i], c[i]); }
}

TEST_F(MatrixTest, TestMultiplyAssign)
{
	Matrix<4, 4> c = a * b;
	Matrix<4, 4> d = a;
	d *= b;
	
	EXPECT_TRUE(c == d);
}

TEST_F(MatrixTest, TestIdentity)
{
	Matrix<4, 4> id = Matrix<4, 4>::Identity();
	
	for(int cl = 0; cl < 4; cl++)
	{
		for(int rw = 0; rw < 4; rw++)
		{
			float v = id.Get(cl, rw);
			
			if(cl == rw)
			{ EXPECT_FLOAT_EQ(v, 1); }
			else
			{ EXPECT_FLOAT_EQ(v, 0); }
		}
	}
}

TEST_F(MatrixTest, TestGet)
{
    int i = a.Get(0, 1);
    ASSERT_FLOAT_EQ(a[1], i);
}

TEST_F(MatrixTest, TestSet)
{
    a.Set(0, 1, 666);
    ASSERT_FLOAT_EQ(a[1], 666);
}

TEST_F(MatrixTest, TestSetColumn)
{
    Matrix<1, 4> m;
    m[0] = 2;
    m[1] = 4;
    m[2] = 6;
    m[3] = 8;

    a.SetColumn(1, m);

    ASSERT_FLOAT_EQ(a[4], 2);
    ASSERT_FLOAT_EQ(a[5], 4);
    ASSERT_FLOAT_EQ(a[6], 6);
    ASSERT_FLOAT_EQ(a[7], 8);
}

TEST_F(MatrixTest, TestSetRow)
{
    Matrix<1, 4> m;
    m[0] = 2;
    m[1] = 4;
    m[2] = 6;
    m[3] = 8;

    a.SetRow(1, m);

    ASSERT_FLOAT_EQ(a[1], 2);
    ASSERT_FLOAT_EQ(a[5], 4);
    ASSERT_FLOAT_EQ(a[9], 6);
    ASSERT_FLOAT_EQ(a[13], 8);
}

TEST_F(MatrixTest, TestIndexFailsOnBadIndex)
{
    ASSERT_DEATH(a[-1], ".*");
    ASSERT_DEATH(a[20], ".*");
}

TEST_F(MatrixTest, TestGetFailsOnBadInput)
{
    ASSERT_DEATH(a.Get(-1, 0), ".*");
    ASSERT_DEATH(a.Get(0, -1), ".*");
    ASSERT_DEATH(a.Get(20, 0), ".*");
    ASSERT_DEATH(a.Get(0, 20), ".*");
}

TEST_F(MatrixTest, TestSetFailsOnBadInput)
{
    ASSERT_DEATH(a.Set(-1, 0, 0), ".*");
    ASSERT_DEATH(a.Set(0, -1, 0), ".*");
    ASSERT_DEATH(a.Set(20, 0, 0), ".*");
    ASSERT_DEATH(a.Set(0, 20, 0), ".*");
}