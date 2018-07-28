#include "Video.hpp"

namespace Egler::Video
{
    GLContext::GLContext(const GLContextData& contextData)
    : window(contextData.WindowName, contextData.WindowDimensions)
    {
        CheckPtr(contextData.Shaders);
        CheckRange(contextData.ShaderCount, MaxShaders);

        shaderCount = contextData.ShaderCount;
        for(int i = 0; i < shaderCount; i++)
        { shaders[i] = Shader(contextData.Shaders[i]); }
    }

    Shader& GLContext::GetShader(int index)
    {
        CheckIndex(index, shaderCount);
        return shaders[index];
    }

    GLWindow& GLContext::Window()
    {
        return window;
    }

    ModelPool& GLContext::Models()
    {
        return models;
    }

    bool GLContext::IsCurrent()
    {
        return window.IsCurrent();
    }

    void GLContext::MakeCurrent()
    {
        window.MakeCurrent();
    }
}