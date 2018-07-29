#pragma once

#include "Egler.hpp"

namespace Egler
{
    MaterialMan::Ptr MaterialMan::Create(EglerContext& egler, const ShaderMan::Ptr& shader)
    {
        if(materials.Count() >= materials.Capacity())
        { throw OutOfMemoryException("Material pool is full (%s values).", materials.Capacity()); }

        Ptr ptr = materials.Allocate();
        Material& mat = materials[ptr];
        Shader& s = egler.Shaders().Get(shader);
        mat.SetShader(s);

        return ptr;
    }

    bool MaterialMan::Exists(const Ptr& ptr)
    {
        return materials.IsAllocated(ptr);
    }

    Material& MaterialMan::Get(const Ptr& ptr)
    {
        if(!Exists(ptr))
        { throw BadArgumentException("Provided material does not exist."); }

        return materials[ptr];
    }

    void MaterialMan::Destroy(EglerContext& egler, const Ptr& ptr)
    {
        materials.Free(ptr);
    }
}