#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    typedef typename EntitySystem<Shader, MaxShaders>::Ptr ShaderPtr;

    class ShaderSystem : public EntitySystem<Shader, MaxShaders>
    {
        public:
            ShaderPtr Create(EglerContext& egler, const ShaderSource& source);
    };
}