#include "Window.hpp"

Window::Window(char const * const name, const PixelRect& dimensions)
{
    assert(name);
    assert(dimensions.Width > -1);
    assert(dimensions.Height > -1);

    window = SDL_CreateWindow(name,
        dimensions.X, dimensions.Y, dimensions.Width, dimensions.Height,
        SDL_WINDOW_OPENGL
    );
    assert(window);

    context = SDL_GL_CreateContext(window);
    assert(context);

    SDL_GL_MakeCurrent(window, context);

    GLenum glewErr = glewInit();
    assert(glewErr == GLEW_OK);

    SDL_GL_SetSwapInterval(1);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    glViewport(0, 0, dimensions.Width, dimensions.Height);
}

Window::~Window()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

void Window::Clear(const Vector4& color, const float depth)
{
    EnsureCurrent();

    glClearColor(color[0], color[1], color[2], color[3]);
    glClearDepth(depth);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Present()
{
    SDL_GL_SwapWindow(window);
}

void Window::EnsureCurrent()
{
    if(SDL_GL_GetCurrentContext() != context)
    { SDL_GL_MakeCurrent(window, context); }
}