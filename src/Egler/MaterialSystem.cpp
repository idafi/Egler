#include "Egler.hpp"

namespace Egler
{
    MaterialSystem::Ptr MaterialSystem::Create(EglerContext& egler, const ShaderPtr& shader)
    {
        Ptr ptr = Allocate();
        Material& mat = Get(ptr);
        Shader& s = egler.Shaders().Get(shader);
        mat.SetShader(s);

        return ptr;
    }
}