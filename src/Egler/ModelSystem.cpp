#include "Egler.hpp"

namespace Egler
{
    ModelSystem::Ptr ModelSystem::Create(EglerContext& egler, const ModelData& modelData)
    {
        Ptr ptr = Allocate();
        Model& model = Get(ptr);
        model.SetData(modelData);

        return ptr;
    }
}