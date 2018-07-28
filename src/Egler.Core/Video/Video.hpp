#pragma once

// - - - - - -
// Video system entry point
// - - - - - -

#include <GL/glew.h>
#include "../Core/Core.hpp"
#include "../Logging/Logging.hpp"

namespace Egler::Video
{
    typedef GLuint VertexArray;
    typedef GLuint VertexBuffer;
    typedef GLuint IndexBuffer;

    static constexpr int MaxModels = 64;
    static constexpr int MaxShaders = 64;
    static constexpr int MaxMaterials = 96;
}

#include "PixelRect.hpp"
#include "ModelData.hpp"
#include "Model.hpp"
#include "ModelPool.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "MaterialPool.hpp"
#include "GLWindow.hpp"
#include "GLContext.hpp"

#define GLEWException(err, msg, ...) \
    FailureException(msg "\n\tGLEW error: %s", ##__VA_ARGS__, glewGetErrorString(err))