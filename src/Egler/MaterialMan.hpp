#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    class MaterialMan
    {
        public:
            typedef typename Pool<Material, Egler::MaxMaterials>::Ptr Ptr;
            
            Ptr Create(EglerContext& egler, const ShaderMan::Ptr& shader);
            bool Exists(const Ptr& ptr);
            void Destroy(EglerContext& egler, const Ptr& ptr);
        
        private:
            Pool<Material, Egler::MaxMaterials> materials;
    };
}