#include "Egler.hpp"

namespace Egler
{
    void Unit::Translate(const Vector3& translation)
    {
        Position += translation;
    }

    void Unit::Rotate(const Quaternion& rotation)
    {
        Rotation *= rotation;
    }

    Mat4 Unit::GetTRSMatrix() const
    {
        Mat4 t = Mat4::Identity();
        Mat4 r = Rotation.ToMatrix();
        Mat4 s = Mat4::Identity();

        Vector4 pos = Vector4(Position.X(), Position.Y(), Position.Z(), 1);
        t.SetColumn(3, pos);
        s.Set(0, 0, Scale.X());
        s.Set(1, 1, Scale.Y());
        s.Set(2, 2, Scale.Z());

        return t * r * s;
    }
}