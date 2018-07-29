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

    Entity& EntityMan::Get(const Ptr& ptr)
    {
        if(!Exists(ptr))
        { throw BadArgumentException("Provided entity does not exist."); }

        return entities[ptr];
    }

    void EntityMan::Update(EglerContext& egler)
    {
        // this doesn't belong here
        static constexpr float cameraFOV = 45;
        static constexpr float zNear = 1;
        static constexpr float zFar = 45;

        // neither does this
        Vector2 windowSize = egler.Window().Size();
        float aspect = windowSize[0] / windowSize[1];
        Matrix pspMatrix = Mat4::Perspective(cameraFOV, zNear, zFar, aspect);

        const byte * const keys = SDL_GetKeyboardState(nullptr);

        for(int i = 0; i < entities.Capacity(); i++)
        {
            if(!entities.IsAllocated(i))
            { continue; }

            Entity& ent = entities[i];
            Model& model = egler.Models().Get(ent.Model);
            Material& material = egler.Materials().Get(ent.Material);

            Vector3 translate;
            if(keys[SDL_SCANCODE_RIGHT])
            { translate[0] += 0.1f; }
            if(keys[SDL_SCANCODE_LEFT])
            { translate[0] -= 0.1f; }
            if(keys[SDL_SCANCODE_UP])
            { translate[1] += 0.1f; }
            if(keys[SDL_SCANCODE_DOWN])
            { translate[1] -= 0.1f; }

            Vector3 scale = ent.GetScale();
            if(keys[SDL_SCANCODE_D])
            { scale[0] += 0.1f; }
            if(keys[SDL_SCANCODE_A])
            { scale[0] -= 0.1f; }
            if(keys[SDL_SCANCODE_W])
            { scale[1] += 0.1f; }
            if(keys[SDL_SCANCODE_S])
            { scale[1] -= 0.1f; }

            ent.Translate(translate.ClampMagnitude(0, 1));
            ent.SetScale(scale);

            material.SetProperty("perspectiveMatrix", pspMatrix);
            material.SetProperty("localToCameraMatrix", ent.TRSMatrix);
            egler.Window().DrawModel(model, material);
        }
    }
}