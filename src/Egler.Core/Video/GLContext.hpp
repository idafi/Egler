#pragma once

#include "Video.hpp"

namespace Egler::Video
{
    struct EGAPI GLContextData
    {
        const char * const WindowName;
        const PixelRect WindowDimensions;

        const ShaderSource * const Shaders;
        const int ShaderCount;

        GLContextData(const char * const windowName, const PixelRect& windowDimensions,
            const ShaderSource * const shaders, const int shaderCount)
        : WindowName(windowName), WindowDimensions(windowDimensions), Shaders(shaders), ShaderCount(shaderCount)
        { }
    };

    class EGAPI GLContext
    {
        public:
            GLContext(const GLContextData& contextData);

            GLWindow& Window();
            Shader& GetShader(int index);
            ModelPool& Models();
            MaterialPool& Materials();

            bool IsCurrent();
            void MakeCurrent();

        private:
            GLWindow window;

            Shader shaders[MaxShaders];
            int shaderCount;

            ModelPool models;
            MaterialPool materials;
    };
}