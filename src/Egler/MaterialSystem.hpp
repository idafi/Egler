#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    typedef typename EntitySystem<Material, MaxMaterials>::Ptr MaterialPtr;

    class MaterialSystem : public EntitySystem<Material, MaxMaterials>
    {
        public:        
            MaterialPtr Create(EglerContext& egler, const ShaderPtr& shader);
    };
}