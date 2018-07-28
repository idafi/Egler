#include "Video.hpp"

namespace Egler::Video
{
    MaterialPool::~MaterialPool()
    {
        materials.Clear();
    }

    Material& MaterialPool::operator [](const Ptr& ptr)
    {
        return materials[ptr];
    }

    int MaterialPool::Capacity()
    {
        return materials.Capacity();
    }

    int MaterialPool::Count()
    {
        return materials.Count();
    }

    MaterialPool::Ptr MaterialPool::Allocate(Shader& shader)
    {
        Ptr ptr = materials.Allocate();
        materials[ptr].SetShader(shader);

        return ptr;
    }

    void MaterialPool::Free(const Ptr& ptr)
    {
        materials.Free(ptr);
    }

    bool MaterialPool::IsAllocated(const Ptr& ptr)
    {
        return materials.IsAllocated(ptr);
    }

    void MaterialPool::Clear()
    {
        materials.Clear();
    }
}