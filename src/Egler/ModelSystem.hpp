#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    typedef typename EntitySystem<Model, MaxModels>::Ptr ModelPtr;

    class ModelSystem : public EntitySystem<Model, MaxModels>
    {
        public:
            ModelPtr Create(EglerContext& egler, const ModelData& modelData);
    };
}