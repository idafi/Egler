#pragma once

#include "Egler.hpp"

namespace Egler
{
    struct Unit
    {
        Vector3 Position;
        Quaternion Rotation;
        Vector3 Scale;

        ModelSystem::Ptr Model;
        MaterialSystem::Ptr Material;

        void Translate(const Vector3& translation);
        void Rotate(const Quaternion& rotation);

        Mat4 GetTRSMatrix() const;
    };
}