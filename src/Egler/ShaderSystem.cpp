#include "Egler.hpp"

namespace Egler
{
    ShaderSystem::Ptr ShaderSystem::Create(EglerContext& egler, const ShaderSource& source)
    {
        Ptr ptr = Allocate();
        Shader& shader = Get(ptr);
        shader.Compile(source);

        return ptr;
    }
}