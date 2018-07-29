#include "Entity.hpp"

namespace Egler::Video
{
    Vector3 Entity::GetPosition()
    {
        Vector4 column = TRSMatrix.GetColumn(3);
        return Vector3(column[0], column[1], column[2]);
    }

    void Entity::SetPosition(const Vector3& position)
    {
        TRSMatrix.SetColumn(3, Vector4(position[0], position[1], position[2], 1));
    }

    Vector3 Entity::GetScale()
    {
        const Mat4& m = TRSMatrix;
        return Vector3(m.Get(0, 0), m.Get(1, 1), m.Get(2, 2));
    }

    void Entity::SetScale(const Vector3& scale)
    {
        TRSMatrix.Set(0, 0, scale.Get(0, 0));
        TRSMatrix.Set(1, 1, scale.Get(1, 1));
        TRSMatrix.Set(2, 2, scale.Get(2, 2));
    }

    void Entity::Translate(const Vector3& translation)
    {
        Vector3 current = GetPosition();
        Vector3 move = current + translation;
        SetPosition(move);
    }
}