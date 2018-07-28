#pragma once

// - - - - - -
// Video system entry point
// - - - - - -

#include <GL/glew.h>
#include "../Core/Core.hpp"
#include "../Logging/Logging.hpp"

typedef GLuint VertexArray;
typedef GLuint VertexBuffer;
typedef GLuint IndexBuffer;

#include "PixelRect.hpp"
#include "ModelBuffer.hpp"
#include "Model.hpp"
#include "ModelPool.hpp"
#include "GLWindow.hpp"
#include "GLContext.hpp"

#define GLEWException(err, msg, ...) \
    FailureException(msg "\n\tGLEW error: %s", ##__VA_ARGS__, glewGetErrorString(err))