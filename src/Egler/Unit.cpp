#include "Egler.hpp"

namespace Egler
{
    Vector3 Unit::GetPosition()
    {
        Vector4 column = TRSMatrix.GetColumn(3);
        return Vector3(column[0], column[1], column[2]);
    }

    void Unit::SetPosition(const Vector3& position)
    {
        TRSMatrix.SetColumn(3, Vector4(position[0], position[1], position[2], 1));
    }

    Vector3 Unit::GetScale()
    {
        const Mat4& m = TRSMatrix;
        return Vector3(m.Get(0, 0), m.Get(1, 1), m.Get(2, 2));
    }

    void Unit::SetScale(const Vector3& scale)
    {
        TRSMatrix.Set(0, 0, scale[0]);
        TRSMatrix.Set(1, 1, scale[1]);
        TRSMatrix.Set(2, 2, scale[2]);
    }

    void Unit::Translate(const Vector3& translation)
    {
        Vector3 current = GetPosition();
        Vector3 move = current + translation;
        SetPosition(move);
    }
}