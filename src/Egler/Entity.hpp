#pragma once

#include "../Egler.Core/Video/Video.hpp"

namespace Egler
{
    struct Entity
    {
        ModelMan::Ptr Model;
        MaterialMan::Ptr Material;
        Mat4 TRSMatrix;

        Vector3 GetPosition();
        void SetPosition(const Vector3& position);

        Vector3 GetScale();
        void SetScale(const Vector3& scale);

        void Translate(const Vector3& translation);
    };
}