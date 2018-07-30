#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    typedef typename EntitySystem<Unit, MaxUnits>::Ptr UnitPtr;

    class UnitSystem : public EntitySystem<Unit, MaxUnits>
    {
        public:
            UnitPtr Create(EglerContext& egler, const ModelPtr& model, const MaterialPtr& material);
            void Update(EglerContext& egler);
        
        private:
            Vector3 GetTranslation(const byte * const keys);
            Quaternion GetRotation(const byte * const keys);
            Vector3 GetScale(const byte * const keys);
    };
}