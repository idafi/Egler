#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    class ModelMan
    {
        public:
            typedef typename Pool<Model, Egler::MaxModels>::Ptr Ptr;
            
            Ptr Create(EglerContext& egler, const ModelData& modelData);
            void Destroy(EglerContext& egler, const Ptr& ptr);
            
            Model& Get(const Ptr& ptr);
            bool Exists(const Ptr& ptr);
            
        private:
            Pool<Model, Egler::MaxModels> models;
    };
}