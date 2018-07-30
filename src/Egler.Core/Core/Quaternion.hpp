#pragma once

#include "Core.hpp"

namespace Egler::Core
{
    struct EGAPI Quaternion
    {
        public:
            Quaternion();
            Quaternion(float x, float y, float z, float w);
            Quaternion(Vector3 euler);

            float& operator [](int c);
            float operator [](int c) const;

            Quaternion operator *(const Quaternion& other) const;
            void operator *=(const Quaternion& other);

            static Quaternion Identity();

            float X() const;
            float Y() const;
            float Z() const;
            float W() const;
            
            float& X();
            float& Y();
            float& Z();
            float& W();

            Vector3 ToEuler() const;
            Mat4 ToMatrix() const;

        private:
            float c[4];
    };
}