#include "Egler.hpp"

namespace Egler
{
    ModelMan::Ptr ModelMan::Create(EglerContext& egler, const ModelData& modelData)
    {
        if(models.Count() > models.Capacity())
        { throw OutOfMemoryException("Model pool is full (%s values).", models.Capacity()); }

        Ptr ptr = models.Allocate();
        Model& model = models[ptr];
        model.SetData(modelData);

        return ptr;
    }

    bool ModelMan::Exists(const Ptr& ptr)
    {
        return models.IsAllocated(ptr);
    }

    Model& ModelMan::Get(const Ptr& ptr)
    {
        if(!Exists(ptr))
        { throw BadArgumentException("Provided model does not exist."); }

        return models[ptr];
    }

    void ModelMan::Destroy(EglerContext& egler, const Ptr& ptr)
    {
        models.Free(ptr);
    }
}