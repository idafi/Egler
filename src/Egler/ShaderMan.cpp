#include "Egler.hpp"

namespace Egler
{
    ShaderMan::Ptr ShaderMan::Create(EglerContext& egler, const ShaderSource& source)
    {
        if(shaders.Count() >= shaders.Capacity())
        { throw OutOfMemoryException("Shader pool is full (%s values).", shaders.Capacity()); }

        Ptr ptr = shaders.Allocate();
        Shader& shader = shaders[ptr];
        shader.Compile(source);

        return ptr;
    }

    void ShaderMan::Destroy(EglerContext& egler, const Ptr& ptr)
    {
        shaders.Free(ptr);
    }

    bool ShaderMan::Exists(const Ptr& ptr)
    {
        return shaders.IsAllocated(ptr);
    }

    Shader& ShaderMan::Get(const Ptr& ptr)
    {
        if(!Exists(ptr))
        { throw BadArgumentException("Provided shader does not exist."); }

        return shaders[ptr];
    }
}