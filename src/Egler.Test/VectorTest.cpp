#include "Egler.Test.hpp"

class VectorTest : public testing::Test
{
    protected:
        VectorTest()
        {
            for(int i = 0; i < Vector4::Size; i++)
            { a[i] = i; }

            b = Vector4::Identity();
        }

        Vector4 a;
        Vector4 b;
};

TEST_F(VectorTest, TestScale)
{
    Vector4 c = a * 6;
    for(int i = 0; i < Vector4::Size; i++)
    { ASSERT_FLOAT_EQ(c[i], i * 6); }
}

TEST_F(VectorTest, TestScaleAssign)
{
    a *= 6;
    for(int i = 0; i < Vector4::Size; i++)
    { ASSERT_FLOAT_EQ(a[i], i * 6); }
}

TEST_F(VectorTest, TestDot)
{
    Vector2 a(0, 1);
    Vector2 b(1, 0);
    ASSERT_FLOAT_EQ(0, a.Dot(b));
}

TEST_F(VectorTest, TestSqrMagnitude)
{
    Vector3 a(1, 0, 0);
    ASSERT_FLOAT_EQ(1, a.SqrMagnitude());

    a = Vector3(-1, -1, -1);
    ASSERT_FLOAT_EQ(3, a.SqrMagnitude());
}

TEST_F(VectorTest, TestMagnitude)
{
    Vector3 a(1, 0, 0);
    ASSERT_FLOAT_EQ(1, a.Magnitude());

    a = Vector3(-1, -1, -1);
    ASSERT_FLOAT_EQ(sqrtf(3), a.Magnitude());
}

TEST_F(VectorTest, TestMagnitudeEmptyVector)
{
    Vector3 a(0, 0, 0);
    ASSERT_FLOAT_EQ(0, a.Magnitude());
}

TEST_F(VectorTest, TestClampMagnitude)
{
    Vector3 a(1, 1, 1);
    a = a.ClampMagnitude(0, 1);
    ASSERT_FLOAT_EQ(1, a.Magnitude());

    a = Vector3(0.5f, 0.5f, 0.5f);
    a = a.ClampMagnitude(1, 2);
    ASSERT_FLOAT_EQ(1, a.Magnitude());
}

TEST_F(VectorTest, TestClampMagnitudeMismatchedBounds)
{
    Vector3 a(1, 1, 1);
    a = a.ClampMagnitude(1, 0);
    ASSERT_FLOAT_EQ(1, a.Magnitude());

    a = Vector3(0.5f, 0.5f, 0.5f);
    a = a.ClampMagnitude(2, 1);
    ASSERT_FLOAT_EQ(1, a.Magnitude());
}

TEST_F(VectorTest, TestClampMagnitudeEmptyVector)
{
    Vector3 a(0, 0, 0);
    a = a.ClampMagnitude(1, 2);
    ASSERT_FLOAT_EQ(0, a.Magnitude());
}

TEST_F(VectorTest, TestClampMagnitudeNegativeBounds)
{
    Vector3 a(1, 1, 1);
    a = a.ClampMagnitude(-1, -2);
    ASSERT_FLOAT_EQ(0, a.Magnitude());
}

TEST_F(VectorTest, TestNormalize)
{
    ASSERT_FLOAT_EQ(1, a.Normalize().Magnitude());
    ASSERT_FLOAT_EQ(1, b.Normalize().Magnitude());
}

TEST_F(VectorTest, TestNormalizeEmptyVector)
{
    Vector3 v(0, 0, 0);
    ASSERT_FLOAT_EQ(0, v.Normalize().Magnitude());
}

TEST_F(VectorTest, TestProject)
{
    Vector2 a(1, 0);
    Vector2 b(1, 2);

    b = b.Project(a);
    ASSERT_FLOAT_EQ(b.Magnitude(), a.Magnitude());
}

TEST_F(VectorTest, TestProjectEmptyVectors)
{
    Vector2 a(0, 0);
    Vector2 b(0, 0);

    ASSERT_FLOAT_EQ(0, a.Magnitude());
    ASSERT_FLOAT_EQ(0, b.Magnitude());
}

TEST_F(VectorTest, TestLerp)
{
    Vector3 a(0, 0, 0);
    Vector3 b(2, 2, 2);

    Vector3 c = Vector3::Lerp(a, b, 0.25f);
    ASSERT_FLOAT_EQ(0.5f, c[0]);
    ASSERT_FLOAT_EQ(0.5f, c[1]);
    ASSERT_FLOAT_EQ(0.5f, c[2]);
}

TEST_F(VectorTest, TestLerpAboveBounds)
{
    Vector3 a(0, 0, 0);
    Vector3 b(2, 2, 2);

    Vector3 c = Vector3::Lerp(a, b, 2);
    ASSERT_FLOAT_EQ(4, c[0]);
    ASSERT_FLOAT_EQ(4, c[1]);
    ASSERT_FLOAT_EQ(4, c[2]);
}

TEST_F(VectorTest, TestLerpBelowBounds)
{
    Vector3 a(0, 0, 0);
    Vector3 b(2, 2, 2);

    Vector3 c = Vector3::Lerp(a, b, -0.25f);
    ASSERT_FLOAT_EQ(-0.5f, c[0]);
    ASSERT_FLOAT_EQ(-0.5f, c[1]);
    ASSERT_FLOAT_EQ(-0.5f, c[2]);
}

TEST_F(VectorTest, TestVector2ToAngle)
{
    Vector2 a(1, 0);
    Vector2 b(1, 1);
    Vector2 c(0, 1);
    Vector2 d(-1, -1);

    ASSERT_FLOAT_EQ(0, a.ToAngle());
    ASSERT_FLOAT_EQ(45, b.ToAngle());
    ASSERT_FLOAT_EQ(90, c.ToAngle());
    ASSERT_FLOAT_EQ(-135, d.ToAngle());
}

TEST_F(VectorTest, TestVector3Cross)
{
    Vector3 a(1, 0, 0);
    Vector3 b(0, 1, 0);

    Vector3 c = a.Cross(b);
    ASSERT_FLOAT_EQ(0, c[0]);
    ASSERT_FLOAT_EQ(0, c[1]);
    ASSERT_FLOAT_EQ(1, c[2]);
}