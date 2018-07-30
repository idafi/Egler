#include "Egler.hpp"

namespace Egler
{
    UnitSystem::Ptr UnitSystem::Create(EglerContext& egler, const ModelPtr& model, const MaterialPtr& material)
    {
        if(!egler.Models().Exists(model))
        { throw BadArgumentException("Provided model does not exist."); }
        if(!egler.Materials().Exists(material))
        { throw BadArgumentException("Provided material does not exist."); }

        Ptr ptr = Allocate();
        Unit& u = Get(ptr);

        u.Model = model;
        u.Material = material;
        u.TRSMatrix = Mat4::Identity();

        return ptr;
    }
    
    void UnitSystem::Update(EglerContext& egler)
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

        for(int i = 0; i < pool.Capacity(); i++)
        {
            if(!pool.IsAllocated(i))
            { continue; }

            Unit& u = pool[i];
            Model& model = egler.Models().Get(u.Model);
            Material& material = egler.Materials().Get(u.Material);

            Vector3 translate;
            if(keys[SDL_SCANCODE_RIGHT])
            { translate[0] += 0.1f; }
            if(keys[SDL_SCANCODE_LEFT])
            { translate[0] -= 0.1f; }
            if(keys[SDL_SCANCODE_UP])
            { translate[1] += 0.1f; }
            if(keys[SDL_SCANCODE_DOWN])
            { translate[1] -= 0.1f; }

            Vector3 scale = u.GetScale();
            if(keys[SDL_SCANCODE_D])
            { scale[0] += 0.1f; }
            if(keys[SDL_SCANCODE_A])
            { scale[0] -= 0.1f; }
            if(keys[SDL_SCANCODE_W])
            { scale[1] += 0.1f; }
            if(keys[SDL_SCANCODE_S])
            { scale[1] -= 0.1f; }

            u.Translate(translate.ClampMagnitude(0, 1));
            u.SetScale(scale);

            material.SetProperty("perspectiveMatrix", pspMatrix);
            material.SetProperty("localToCameraMatrix", u.TRSMatrix);
            egler.Window().DrawModel(model, material);
        }
    }
}