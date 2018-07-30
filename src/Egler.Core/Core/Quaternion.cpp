#include "Core.hpp"

namespace Egler::Core
{
    Quaternion::Quaternion()
    {
        memset(c, 0, sizeof(c));
    }

    Quaternion::Quaternion(float x, float y, float z, float w)
    {
        c[0] = x;
        c[1] = y;
        c[2] = z;
        c[3] = w;
    }

    Quaternion::Quaternion(Vector3 euler)
    {
        float yaw = Deg2Rad(euler[0]) * 0.5f;
        float pitch = Deg2Rad(euler[1]) * 0.5f;
        float roll = Deg2Rad(euler[2]) * 0.5f;

        float cy = cos(yaw);
        float sy = sin(yaw);
        float cp = cos(pitch);
        float sp = sin(pitch);
        float cr = cos(roll);
        float sr = sin(roll);

        c[0] = cy * sr * cp - sy * cr * sp;
        c[1] = cy * cr * sp + sy * sr * cp;
        c[2] = sy * cr * cp - cy * sr * sp;
        c[3] = cy * cr * cp + sy * sr * sp;
    }

    float& Quaternion::operator [](int c)
    {
        CheckIndex(c, 4);
        return this->c[c];
    }

    float Quaternion::operator [](int c) const
    {
        CheckIndex(c, 4);
        return this->c[c];
    }

    Quaternion Quaternion::operator *(const Quaternion& other) const
    {
        float x = (c[3] * other[0]) + (c[0] * other[3]) + (c[1] * other[2]) - (c[2] * other[1]);
        float y = (c[3] * other[1]) + (c[1] * other[3]) + (c[2] * other[0]) - (c[0] * other[2]);
        float z = (c[3] * other[2]) + (c[2] * other[3]) + (c[0] * other[1]) - (c[1] * other[0]);
        float w = (c[3] * other[3]) - (c[0] * other[0]) - (c[1] * other[1]) - (c[2] * other[2]);

        return Quaternion(x, y, z, w);
    }

    void Quaternion::operator *=(const Quaternion& other)
    {
        *this = *this * other;
    }

    Quaternion Quaternion::Identity()
    {
        return Quaternion(0, 0, 0, 1);
    }

    float Quaternion::X() const
    {
        return c[0];
    }

    float Quaternion::Y() const
    {
        return c[1];
    }

    float Quaternion::Z() const
    {
        return c[2];
    }

    float Quaternion::W() const
    {
        return c[3];
    }

    float& Quaternion::X()
    {
        return c[0];
    }

    float& Quaternion::Y()
    {
        return c[1];
    }

    float& Quaternion::Z()
    {
        return c[2];
    }

    float& Quaternion::W()
    {
        return c[3];
    }

    Vector3 Quaternion::ToEuler() const
    {
        float sy = 2 * (c[3] * c[2] + c[0] * c[1]);
        float cy = 1 - 2 * (c[1] * c[1] + c[2] * c[2]);
        float yaw = atan2(sy, cy);

        float sp = 2 * (c[3] * c[1] - c[2] * c[0]);
        float pitch = (fabs(sp) >= 1)
            ? copysign(M_PI / 2, sp)  // use 90 degrees if out of range
            : asin(sp);

        float sr = 2 * (c[3] * c[0] + c[1] * c[2]);
        float cr = 1 - 2 * (c[0] * c[0] + c[1] * c[1]);
        float roll = atan2(sr, cr);

        return Vector3(Rad2Deg(yaw), Rad2Deg(pitch), Rad2Deg(roll));
    }
}