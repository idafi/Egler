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
        u.Position = Vector3(0, 0, 0);
        u.Rotation = Quaternion::Identity();
        u.Scale = Vector3(1, 1, 1);

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

        Vector3 translate;
        if(keys[SDL_SCANCODE_RIGHT])
        { translate.X() += 0.1f; }
        if(keys[SDL_SCANCODE_LEFT])
        { translate.X() -= 0.1f; }
        if(keys[SDL_SCANCODE_UP])
        { translate.Y() += 0.1f; }
        if(keys[SDL_SCANCODE_DOWN])
        { translate.Y() -= 0.1f; }

        Vector3 rotate;
        if(keys[SDL_SCANCODE_E])
        { rotate.X() += 1; }
        if(keys[SDL_SCANCODE_Q])
        { rotate.X() -= 1; }
        if(keys[SDL_SCANCODE_T])
        { rotate.Y() += 1; }
        if(keys[SDL_SCANCODE_G])
        { rotate.Y() -= 1; }

        Vector3 scale;
        if(keys[SDL_SCANCODE_D])
        { scale.X() += 0.1f; }
        if(keys[SDL_SCANCODE_A])
        { scale.X() -= 0.1f; }
        if(keys[SDL_SCANCODE_W])
        { scale.Y() += 0.1f; }
        if(keys[SDL_SCANCODE_S])
        { scale.Y() -= 0.1f; }

        uint ticks = SDL_GetTicks();
        float t = (float)(ticks % 5000) / 5000;

        for(int i = 0; i < pool.Capacity(); i++)
        {
            if(!pool.IsAllocated(i))
            { continue; }

            Unit& u = pool[i];
            Model& model = egler.Models().Get(u.Model);
            Material& material = egler.Materials().Get(u.Material);

            u.Translate(translate.ClampMagnitude(0, 1));
            u.Rotate(Quaternion(rotate));
            u.Scale += scale;
            
            material.SetProperty("perspectiveMatrix", pspMatrix);
            material.SetProperty("localToCameraMatrix", u.GetTRSMatrix());
            material.SetProperty("t", t);
            egler.Window().DrawModel(model, material);
        }
    }
}