#pragma once

#include "Video.hpp"

namespace Egler::Video
{
    class MaterialPool
    {
        public:
            typedef typename Pool<Material, MaxMaterials>::Ptr Ptr;

            ~MaterialPool();

            int Capacity();
            int Count();

            Ptr Allocate(Shader& shader);
            void Free(const Ptr& ptr);
            bool IsAllocated(const Ptr& ptr);
            void Clear();

        private:
            Pool<Material, MaxMaterials> materials;
    };
}