#include "../Egler.Test.hpp"

namespace Egler::Core
{
    class QuaternionTest : public testing::Test
    { };

    TEST_F(QuaternionTest, TestEulerRoundTrip)
    {
        Vector3 euler(30, 60, 90);
        Quaternion quat(euler);
        Vector3 trip = quat.ToEuler();

        ASSERT_NEAR(30, trip[0], 0.0001f);
        ASSERT_NEAR(60, trip[1], 0.0001f);
        ASSERT_NEAR(90, trip[2], 0.0001f);
    }

    TEST_F(QuaternionTest, TestCopyIndexing)
    {
        Quaternion q(1, 2, 3, 4);
        float x = q[0];
        float y = q[1];
        float z = q[2];
        float w = q[3];

        ASSERT_FLOAT_EQ(1, x);
        ASSERT_FLOAT_EQ(2, y);
        ASSERT_FLOAT_EQ(3, z);
        ASSERT_FLOAT_EQ(4, w);
    }

    TEST_F(QuaternionTest, TestRefIndexing)
    {
        Quaternion q(1, 2, 3, 4);
        q[0] = 5;
        q[1] = 6;
        q[2] = 7;
        q[3] = 8;

        ASSERT_FLOAT_EQ(5, q[0]);
        ASSERT_FLOAT_EQ(6, q[1]);
        ASSERT_FLOAT_EQ(7, q[2]);
        ASSERT_FLOAT_EQ(8, q[3]);
    }

    TEST_F(QuaternionTest, TestMultiplication)
    {
        Quaternion qA(Vector3(30, 0, 0));
        Quaternion qB(Vector3(0, 60, 0));
        Quaternion qC(Vector3(0, 0, 90));

        Quaternion qD = qA * qB * qC;
        Vector3 euler = qD.ToEuler();

        ASSERT_NEAR(30, euler[0], 0.0001f);
        ASSERT_NEAR(60, euler[1], 0.0001f);
        ASSERT_NEAR(90, euler[2], 0.0001f);
    }

    TEST_F(QuaternionTest, TestAssignMultiplication)
    {
        Quaternion qA(Vector3(30, 0, 0));
        Quaternion qB(Vector3(0, 60, 0));
        Quaternion qC(Vector3(0, 0, 90));

        qA *= qB * qC;
        Vector3 euler = qA.ToEuler();

        ASSERT_NEAR(30, euler[0], 0.0001f);
        ASSERT_NEAR(60, euler[1], 0.0001f);
        ASSERT_NEAR(90, euler[2], 0.0001f);
    }
}