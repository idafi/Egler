#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    class EglerContext
    {
        public:
            EglerContext() { }
            EglerContext(const char * const windowName, const PixelRect& windowDim)
            : window(GLWindow(windowName, windowDim)) { }

            GLWindow& Window()
            { return window; }
            ShaderSystem& Shaders()
            { return shaders; }
            ModelSystem& Models()
            { return models; }
            MaterialSystem& Materials()
            { return materials; }
            UnitSystem& Units()
            { return units; }
        
        private:
            GLWindow window;
            
            ShaderSystem shaders;
            ModelSystem models;
            MaterialSystem materials;
            UnitSystem units;
    };
}