#pragma once

#include "Egler.hpp"

using namespace Egler::Video;

namespace Egler
{
    class EntityMan
    {
        public:
            typedef typename Pool<Entity, Egler::MaxEntities>::Ptr Ptr;
            
            Ptr Create(EglerContext& egler, const ModelMan::Ptr& model, const MaterialMan::Ptr& material);
            void Destroy(EglerContext& egler, const Ptr& ptr);

            bool Exists(const Ptr& ptr);
            Entity& Get(const Ptr& ptr);
            
            void Update(EglerContext& egler);
        
        private:
            Pool<Entity, Egler::MaxEntities> entities;
    };
}