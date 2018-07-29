#include "Egler.hpp"

namespace Egler
{
    EntityMan::Ptr EntityMan::Create(EglerContext& egler, const ModelMan::Ptr& model, const MaterialMan::Ptr& material)
    {
        if(entities.Count() >= entities.Capacity())
        { throw OutOfMemoryException("Entity pool is full (%s values).", entities.Capacity()); }
        if(!egler.Models().Exists(model))
        { throw BadArgumentException("Provided model does not exist."); }
        if(!egler.Materials().Exists(material))
        { throw BadArgumentException("Provided material does not exist."); }

        Ptr ptr = entities.Allocate();
        Entity& ent = entities[ptr];
        ent.Model = model;
        ent.Material = material;
        ent.TRSMatrix = Mat4::Identity();

        return ptr;
    }

    void EntityMan::Destroy(EglerContext& egler, const EntityMan::Ptr& ptr)
    {
        entities.Free(ptr);
    }

    bool EntityMan::Exists(const Ptr& ptr)
    {
        return entities.IsAllocated(ptr);
    }

    void EntityMan::Update(EglerContext& egler)
    {
        
    }
}