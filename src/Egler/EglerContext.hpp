#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    class EglerContext
    {
        public:
            GLWindow& Window()
            { return window; }
            ShaderMan& Shaders()
            { return shaders; }
            ModelMan& Models()
            { return models; }
            MaterialMan& Materials()
            { return materials; }
            EntityMan& Entities()
            { return entities; }
        
        private:
            GLWindow window;
            
            ShaderMan shaders;
            ModelMan models;
            MaterialMan materials;
            EntityMan entities;
    };
}