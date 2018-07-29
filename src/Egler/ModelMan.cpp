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

    void ModelMan::Destroy(EglerContext& egler, const Ptr& ptr)
    {
        models.Free(ptr);
    }
}