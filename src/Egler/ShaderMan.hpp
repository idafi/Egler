#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    class ShaderMan
    {
        public:
            typedef typename Pool<Shader, Egler::MaxShaders>::Ptr Ptr;
            
            Ptr Create(EglerContext& egler, const ShaderSource& source);
            bool Exists(const Ptr& ptr);
            void Destroy(EglerContext& egler, const Ptr& ptr);
        
        private:
            Pool<Shader, Egler::MaxShaders> shaders;
    };
}