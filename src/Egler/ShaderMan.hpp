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
            void Destroy(EglerContext& egler, const Ptr& ptr);
            
            bool Exists(const Ptr& ptr);
            Shader& Get(const Ptr& ptr);
        
        private:
            Pool<Shader, Egler::MaxShaders> shaders;
    };
}